# Laboratory 1

## Deliverable

A zip file containing:

- A folder called `ex0`, with a text file with a small description of how are you going to be running your lab. In a Linux, a Linux VM, Docker, Mac, or any choice. This will guide me to know how to grade your lab, therefore it's very important.
- A folder called `ex1`, with a file or files for the Excercise 1. You can write it in a text file, word file, pdf file, whatever you are more comfortable with.
- A folder called `ex2`, with the code files for the Excercise 2. Including the proper instructions on how to run it. It is expected that you write your **own** code.
- A folder called `ex3`, with the code files for the Excercise 3. Including the proper instructions on how to run it and detailing which tool will you be using. Please do **NOT** include any credentials for your GCP or AWS accounts if you chose this path. Just add a README detailing the name of the resources I need to create to test it. You can reuse code from the docs of the tool of your choosing, as long as you cite your source.
- A folder called `ex4`, with the code files for the Excercise 4. Including the proper instructions on how to run it. It is expected that you write your **own** code.

## Excercise 0 (optional)

Install VirtualBox or Docker to run the rest of the lab. You can run the commands in your own computer at your own risk.

Install links for Docker:

- https://docs.docker.com/engine/install/ubuntu/
- https://docs.docker.com/desktop/windows/install/
- https://docs.docker.com/desktop/mac/install/

Install links for VirtualBox:

- https://www.virtualbox.org/wiki/Downloads
- https://ubuntu.com/download/desktop
- https://ubuntu.com/download/server

## Excercise 1 - Debugging syscalls

Run a syscall analysis, using `strace` for example for Linux, to the commands:
- `echo "Hello World"`
- `ls -la`
- `pwd`
- `ping -c 1 8.8.8.8`
- a Hello World C Program 

Then, write down a description of the system calls that are being called. The description should be in-depth and not superficial, you can google the syscalls that you don't know (or check this website https://linuxhint.com/list_of_linux_syscalls/) and try to infer from the parameters what are they doing and if they are used in the same order in all of the executions. There is a hello.c file located in the `ex1` folder. 

To run this excercise in a Linux environment you can do:

```bash
cd ex1
# to run strace
strace echo "Hello World"
# to run the hello.c code
gcc hello.c -o hello
./hello
```

Alternatively, to run it in Docker, you can do:
```bash
cd ex1
docker build -t lab1_ex1 .
docker run --rm -ti lab1_ex1 strace echo "Hello World"
# This is an alternative way of calling strace, what's the -e flag?
docker run --rm -ti lab1_ex1 strace -e trace=read echo "Hello"
# This is how to run a docker to run the strace in the hello command
docker run --rm -ti -v $(pwd)/:/root/lab lab1_ex1 /bin/bash -c "cd /root/lab; gcc -o hello hello.c; strace ./hello"
```

Strace manpage:
http://manpages.ubuntu.com/manpages/bionic/man1/strace.1.html


#### Bonus (in the name of knowledge)

Write a Dockerfile that removes the need to attach a volume and compile the file in that line, so that you can only do:

```bash
docker run --rm -ti lab1_ex1 strace ./root/hello
```

## Excercise 2 - Shared Memory

Relying on the provided files, write a chat program, based on two **C programs** using shared memory (not pipes, nor fifo). 

You can safely assume that the messages won't be long, between 1024 and 4096 bytes is more than enough. You can also assume that only one person will chat at the same time, meaning that only one of the two users can send text at the same time, this does not mean that that one user is limited to one message. This means that, user1 writes and he could write again multiple times, after user2 can reply with one or more messages.

You can do it by using fork, by writing two different programs or any other way you prefer. Whatever option you choose, make sure to write the proper instructions (inside a README file) on how to run your code.

All necessary files are located in the `ex2` folder. Keep in mind that there are some examples for `fork`, `pipes`, and `shared memory`.

## Excercise 3 - Advanced Message Passing

Write a program in the language of your chosing, that consist of two files, a publisher and a suscriber. The publisher, as the word describes it, it will publish a message read from the keyboard. The suscriber, will run endlessly showing all messages. You will have to chose between using Google Pub/Sub, Amazon SQS or a local Redis. 

All of those tools are well documented and heavily used in the industry. If you want to go one step beyond you can integrate Amazon SNS and Amazon SQS.

Here are some reference links:

- https://cloud.google.com/pubsub/
- https://aws.amazon.com/sqs/
- https://redis.io/topics/pubsub
- https://aws.amazon.com/sns/

The differences are:

- For Google Cloud, you need to create an account, it's "free", and create the topic and suscriber for it to work.
- For Amazon Web Services, you also need to create an account, it's also "free", and create the queue for it to work.
- For Redis, you need to create a local container or install redis (not recommended), and then expose the ports, therefore you need to research more about Docker and running containers.

Quick example for Google Cloud Pub/Sub relying on the cli:
```bash
docker run --rm -ti -v $HOME/.config/gcloud:/root/.config/gcloud google/cloud-sdk gcloud init
docker run --rm -ti -v $HOME/.config/gcloud:/root/.config/gcloud google/cloud-sdk gcloud auth login
docker run --rm -ti -v $HOME/.config/gcloud:/root/.config/gcloud google/cloud-sdk gcloud pubsub topics publish belt-test --message "Test message" --attribute url=http://www.bla.com,foo=bar
docker run --rm -ti -v $HOME/.config/gcloud:/root/.config/gcloud google/cloud-sdk gcloud pubsub subscriptions pull projects/assistant-backend-dev/subscriptions/belt-sub --auto-ack --format='flattened'
```

## Excercise 4 - syscalls libraries

Write a program in your favorite programming language and make 6 different system calls. Make sure to add some comments to which syscalls are you using, why the arguments and make sure to have proper guidelines on how to run the code.

For Python look for `ctypes` library, for GoLang look for `syscall` packge, for Java look for `JNA` library, etc. Also do some research about how the programming language you are using handles syscalls, if it has a native way or not. You can also research other libraries that can be used for calling syscalls and chose the one you prefer.