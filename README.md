This project is ASR-IOT project: smart home from scratch
input: audio
output: executes the input command

### Main Challenges:
due to the limitation of the hardware(CPU and memory) and compatibilities, we have to deal with challenges to optimize the process.
- memory management
- latency
- data loss
- sampling rate
- noise

ASR model:
  - Google Cloud Speech-to-Text
  - (optional) builds your own model using Kaldi toolkit
  
Hardware requirements:
  - STM32F4-Discovery board
  - ESP8266 (for WIFI connection) 
  - microphone sensor
  - (optional)other IOT devices

in progress:
  - speaker verification
  - natural language understanding


