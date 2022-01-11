import os
from google.cloud import pubsub_v1

credentials_path = '/Users/estellezheng/Documents/M1 2021:2022/S1/Computer\ Science/lldm/lldm\ \-\ lab1/ex3/lab1-lldm-privatekey.json'
os.environ['GOOGLE_APPLICATION_CREDENTIALS'] = credentials_path
# TODO(developer)
# project_id = "Project-LLDM"
# topic_id = "Project-LLDM-sub"

publisher = pubsub_v1.PublisherClient()
# The `topic_path` method creates a fully qualified identifier
# in the form `projects/{project_id}/topics/{topic_id}`
topic_path = 'projects/fabled-electron-332410/topics/Project-LLDM'

while(1):
    data = input()
    # Data must be a bytestring
    data = data.encode("utf-8")
    # When you publish a message, the client returns a future.
    future = publisher.publish(topic_path, data)
    print(future.result())
    print(f"Published messages to {topic_path}.")



