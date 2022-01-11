# Exercice 3 

## Disclaimer
**Python 3.9.5** was used for this exercice.

Every code used for this exercice was extracted from **Google Pub/Sub** website, where all the code samples are licensed under the Apache 2.0 License.

Some modifications were done using the knowledge of Youtube videos and myself.

## Modifications
- The first modification was importing the `os library`, to be able to use the credentials path. The `privatekey.json` to this program can be found in this directory.

```bash
import os

credentials_path = 'ABSOLUTE PATH to privatekey.json file'
os.environ['GOOGLE_APPLICATION_CREDENTIALS'] = credentials_path
```

- The second modification was about setting up the proper path for the topic and the subscriber.

```python
# Must be set up on publisher.py
topic_path = 'projects/fabled-electron-332410/topics/Project-LLDM'
# Must be set up on subscriber.py
subscription_path = 'projects/fabled-electron-332410/subscriptions/Project-LLDM-sub'
```

- The third modification was to create the message from a keyboard input. Making it an infinite loop, press **CTRL + D** to exit.

```python
while(1):
    data = input()
```

- The fourth and last modification was about not setting up any timeout, it means as long as nothing has been input; then the program is just waiting for an input.

```python
## Originally the timeout was set up to 5 secs
# timeout = 5.0
streaming_pull_future.result(timeout = timeout)

## We just wait indefinitely until an input
streaming_pull_future.result()
```

## Need to be set up before running the code

- `python3` has to be installed.
- `google.cloud` library has to be installed. 

```bash
## if pip was not installed
# On Ubuntu 20.4
sudo apt install python3-pip
# On Mac OS
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
python3 get-pip.py

# the actual install of google-cloud
pip install --upgrade google-cloud-pubsub
```
	
- The `ABSOLUTE PATH` to `privatekey.json` should be modified as this file may be in a completely different path from before. 

## Running the code
Open two terminals, one for `publisher.py` and the other one for `subscriber.py`.

```bash
# Terminal 1
python3 publisher.py
# input your message
# to stop publishing, press CTRL + D
```
```bash
# Terminal 2
python3 subscriber.py
# each message is received here
# need to manually exit the terminal if finished publishing
```