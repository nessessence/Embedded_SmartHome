# Embedded_SmartHome101
This project is ASR-IOT project from scratch 

STM32F4-Discovery Project: SmartHome101
- input: audio
- output: execute the input command

### Main Challenges:
due to the limitation of the hardware(CPU and memory) and compatibilities, we have to deal with challenges to optimize the process.
- memory management
- latency
- data loss
- sampling rate
- noise

ASR model:
  - Google Cloud Speech-to-Text
  - (optional) create your own model using Kaldi toolkit
  
Hardware requirements:
  - STM32F4-Discovery board
  - ESP8266 (for WIFI connection) 
  - microphone sensor
  - (optional)other IOT devices

in progress:
  - speaker verification
  - natural language understanding


