import asyncio
import glob
import json
import re
import shutil
import time
import urllib.request
import os.path
import win32com.client
import music_tag

import requests
import spotipy

from shazamio import Shazam, Serialize
from moviepy.editor import *
from mutagen.easyid3 import EasyID3
from mutagen.id3 import APIC, ID3
from pytube import YouTube
from rich.console import Console
from spotipy.oauth2 import SpotifyClientCredentials


CONFIG_FILE_PATH = r"C:\Users\marti\Desktop\musicConf.json"
MUSIC_FOLDER_PATH = r"C:\Users\marti\Music"

"""
metadata provided by shazam
title - song name
subtitle - artist ig
images, coverart

artist
title
album_art
"""


async def main():
    load_config()

    x = check_if_song_is_downloaded_on_disk_tag("639053666")


    shazam = Shazam()
    top_world_tracks = await shazam.top_world_tracks(limit=100)
    songs: list = []

    # store song metadata
    track: dict = {}
    for track in top_world_tracks["tracks"]:
        print(track["title"] + " " + track["subtitle"])

        # fix songs without thumbnail
        trackImage: dict = track.setdefault("images", {"coverart": "https://cdn-icons-png.flaticon.com/512/3844/3844724.png"})
        if "http" not in trackImage["coverart"]:
            trackImage = "https://cdn-icons-png.flaticon.com/512/3844/3844724.png"

        songs.append({"title": track["title"], "artist": track["subtitle"], "album_art": trackImage["coverart"], "tracknumber": track["key"]})


    print("    #     |             Song name           | is downloaded")

    for song in songs:

        if check_if_song_is_downloaded_on_disk_tag(song["tracknumber"]):
            print_song_status(song["tracknumber"],song["title"]+" "+ song["artist"],"allready downloaded")
            continue
        if check_if_song_is_blacklisted_key(song["tracknumber"]):
            print_song_status(song["tracknumber"], song["title"]+" "+ song["artist"], "blacklisted")
            continue

        try:
            ytLink = find_youtube(song["title"] + " " + song["artist"])
            filePath = download_yt(ytLink)
            set_metadata(song, filePath)
            print_song_status(song["tracknumber"],song["title"]+" "+ song["artist"],"downloaded")
        except:
            add_blacklisted_song_key(song["tracknumber"])
            print_song_status(song["tracknumber"], song["title"]+" "+ song["artist"], "failed")



def print_song_status(songKey:str,songName,song_status: str):
    songKey = songKey.center(10, " ")+"|"
    if len(songName)>30:
        songName = songName[:30] + "..."
    songName = songName.center(33, " ")+"|"
    song_status = song_status.center(15, " ")
    print(f"{songKey}{songName}{song_status}")

def load_config():
    if not os.path.exists(CONFIG_FILE_PATH):
        f = open(CONFIG_FILE_PATH, "x")
        f.close()
        f = open(CONFIG_FILE_PATH, "w")
        f.write(json.dumps({"blackListedSongs": [0]}))
        f.close()

    f = open(CONFIG_FILE_PATH)
    global fileContents
    jsonText = f.readline()
    fileContents = json.loads(jsonText)
    f.close()

def check_if_song_is_downloaded_on_disk_tag(songkey):
    files = glob.glob(f"{MUSIC_FOLDER_PATH}\*.mp3")
    for file in files:
        songFile = music_tag.load_file(file)
        if str(songFile["tracknumber"]) == songkey:
            return True
    return False


def add_blacklisted_song_key(songKey):
    # read config file for downloaded songs
    f = open(CONFIG_FILE_PATH, "r")
    data = f.read()
    f.close()
    jsonDict = json.loads(data)

    # add song to downloaded list and save to file
    jsonDict["blackListedSongs"].append(songKey)
    data = json.dumps(jsonDict)
    f = open(CONFIG_FILE_PATH, "w")
    f.write(data)
    f.close()


def check_if_song_is_blacklisted_key(songKey):
    # read config file for downloaded songs
    f = open(CONFIG_FILE_PATH, "r")
    data = f.read()
    f.close()
    jsonDict = json.loads(data)

    if songKey in jsonDict["blackListedSongs"]:
        return True
    else:
        return False


def find_youtube(query):
    phrase = query.replace(" ", "+")
    search_link = "https://www.youtube.com/results?search_query=" + phrase
    count = 0
    while count < 3:
        try:
            response = urllib.request.urlopen(search_link)
            break
        except:
            count += 1
    else:
        raise ValueError("Please check your internet connection and try again later.")

    search_results = re.findall(r"watch\?v=(\S{11})", response.read().decode())
    first_vid = "https://www.youtube.com/watch?v=" + search_results[0]

    return first_vid


def download_yt(yt_link):
    """download the video in mp3 format from youtube"""
    yt = YouTube(yt_link)
    # remove chars that can't be in a windows file name
    yt.title = "".join([c for c in yt.title if c not in ['/', '\\', '|', '?', '*', ':', '>', '<', '"']])

    # download the music
    video = yt.streams.filter(only_audio=True).first()
    vid_file = video.download(output_path=MUSIC_FOLDER_PATH)
    # convert the downloaded video to mp3
    base = os.path.splitext(vid_file)[0]
    audio_file = base + ".mp3"
    mp4_no_frame = AudioFileClip(vid_file)
    mp4_no_frame.write_audiofile(audio_file, logger=None)
    mp4_no_frame.close()
    os.remove(vid_file)
    os.replace(audio_file, f"{MUSIC_FOLDER_PATH}\\{yt.title}.mp3")
    audio_file = f"{MUSIC_FOLDER_PATH}\\{yt.title}.mp3"
    return audio_file


def set_metadata(metadata, file_path):
    """adds metadata to the downloaded mp3 file
    metadata e dictionary i file path e linko do audio filo"""

    mp3file = EasyID3(file_path)

    # add metadata
    mp3file["artist"] = metadata["artist"]
    mp3file["title"] = metadata["title"]
    mp3file["tracknumber"] = metadata["tracknumber"]
    mp3file.save()

    # add album cover
    audio = ID3(file_path)
    with urllib.request.urlopen(metadata["album_art"]) as albumart:
        audio["APIC"] = APIC(
            encoding=3, mime="image/jpeg", type=3, desc="Cover", data=albumart.read()
        )
    audio.save(v2_version=3)

def get_file_metadata(path, filename, metadata):
    # Path shouldn't end with backslash, i.e. "E:\Images\Paris"
    # filename must include extension, i.e. "PID manual.pdf"
    # Returns dictionary containing all file metadata.
    sh = win32com.client.gencache.EnsureDispatch('Shell.Application', 0)
    ns = sh.NameSpace(path)

    # Enumeration is necessary because ns.GetDetailsOf only accepts an integer as 2nd argument
    file_metadata = dict()
    item = ns.ParseName(str(filename))
    for ind, attribute in enumerate(metadata):
        attr_value = ns.GetDetailsOf(item, ind)
        if attr_value:
            file_metadata[attribute] = attr_value

    return file_metadata

loop = asyncio.get_event_loop()
loop.run_until_complete(main())
