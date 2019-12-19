import json
from flask import Flask, request,jsonify
# from baseline_main import speech_to_text
# from mock import speech_to_text
from flask_cors import CORS

app = Flask(__name__)
lastest_words = "reading"
cors = CORS(app)



d = {}
az = "abcdefghijklmnopqrstuvwxyz"
for i in range(len(az)):
    d[az[i]] = i

def mapping(a,b):
    return d[a]*10 + int(b)

def all_mapping(z):
    for i in range(0,len(z),2):
        wavelist.append(mapping(z[i], z[i+1]))


# make wave sound#
import numpy as np  
import scipy.io.wavfile as wp
import soundfile

def makeWaveFile(wl):
    arr = np.array(wl,dtype = np.uint8)
    wp.write("raw.wav",len(wl)//3,arr)
    data, samplerate = soundfile.read('raw.wav')
    soundfile.write("audio.wav", data, 8000, subtype='PCM_16')

import io
import os
# ASR part #
from google.cloud import speech
from google.cloud.speech import enums
from google.cloud.speech import types

transcripts = []
client = speech.SpeechClient.from_service_account_json("nessspeech.json")
filename = "audio.wav"
color = ["green","orange","red","blue"]

def make_command(ts) :
    global color
    command = [1,1,1,1]
    c = 0
    if "on" in ts or "on." in ts : x = 2
    elif "off" in ts or "off." in ts: x = 0
    else : x = 1
    for i in range(len(command)):
        if color[i] in ts: 
            print("turn the",color[i],x) #just check 
            command[i] = x 
            c += 1
    if c == 0 :
        command = [x,x,x,x]
    return command
def speech_to_text():
    global client,filename,transcripts
    with io.open(filename, 'rb') as audio_file:
        content = audio_file.read()
        audio = types.RecognitionAudio(content=content)
    config = types.RecognitionConfig(encoding=enums.RecognitionConfig.AudioEncoding.LINEAR16,
                                    sample_rate_hertz=8000,language_code='en-US')
    response = client.recognize(config, audio)
    #transcripts = [str(s) for s in ((response.results[0]).alternatives[0].transcript).split(" ")]
    for result in response.results:
        #print('{}'.format(result.alternatives[0].transcript))
        transcripts = '{}'.format(result.alternatives[0].transcript).split(" ")
    ts_clean = []
    for cm in transcripts:
        tmp_cm = cm.strip().lower().replace('.','')
        ts_clean.append(tmp_cm)
    print(ts_clean)
    return ts_clean



wavelist = []
counting = 0


@app.route('/', methods = ["POST", "GET"])

def post():
    global counting,wavelist,d,az,lastest_words,command
    if request.method == 'POST':
        req_data = request.get_json()
        data = req_data['f']
        if counting == 0:
            wavelist=[]
        all_mapping(data)
        counting += 1
        if counting == 8:
            print(len(wavelist))
            #print(wavelist)
            makeWaveFile(wavelist)
            transcriptions = speech_to_text() #command: [1,0,0,0] , word: "hsjs dg"
            command = make_command(transcriptions) 
            lastest_words = transcriptions
            result = "".join(map(str, command))
            print(result)
            wavfile = []
            counting = 0
            return result
        else:
            print("success #" + str(counting))
            return "success #" + str(counting)
        # print(wavfile)
        # command = speech_to_text(wavfile)
                
    if request.method == 'GET':
        # return jsonify({"word": lastest_word,"result": result})
        return jsonify({"word": " ".join(lastest_words), "result": command})

app.run(host='localhost', port= 8090)
