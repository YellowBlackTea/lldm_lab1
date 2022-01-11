import os
from concurrent.futures import TimeoutError
from google.cloud import pubsub_v1

credentials_path = '/Users/estellezheng/Documents/M1 2021:2022/S1/Computer\ Science/lldm/lldm\ \-\ lab1/ex3/lab1-lldm-privatekey.json'
os.environ['GOOGLE_APPLICATION_CREDENTIALS'] = credentials_path

# TODO(developer)
# project_id = "Project-LLDM"
# topic_id = "Project-LLDM-sub"
# Number of seconds the subscriber should listen for messages
# timeout = 5.0

subscriber = pubsub_v1.SubscriberClient()
# The `subscription_path` method creates a fully qualified identifier
# in the form `projects/{project_id}/subscriptions/{subscription_id}`
# subscription_path = subscriber.subscription_path(project_id, subscription_id)
subscription_path = 'projects/fabled-electron-332410/subscriptions/Project-LLDM-sub'

def callback(message: pubsub_v1.subscriber.message.Message) -> None:
    print(f'Received {message}.')
    message.ack()

streaming_pull_future = subscriber.subscribe(subscription_path, callback=callback)
print(f"Listening for messages on {subscription_path}..\n")

# Wrap subscriber in a 'with' block to automatically call close() when done.
with subscriber:
    try:
        # When `timeout` is not set, result() will block indefinitely,
        # unless an exception is encountered first.
        streaming_pull_future.result()
    except TimeoutError:
        streaming_pull_future.cancel()  # Trigger the shutdown.
        streaming_pull_future.result()  # Block until the shutdown is complete.