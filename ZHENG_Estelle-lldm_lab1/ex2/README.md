# Exercice 2

## Disclaimer

Every code has been written using what Dr. José Alfredo Alvarez Aldana gives as examples for `shared memory` and `fork`.

## What was used

Many choices were offered, but I used `shared memory` with `fork` because it was easier to understand for me.

Everything could have ben written in a `main` function, but it was too messy for my own understanding. I created another function called `createSharedMem()` which is actually just the **mapping** of the shared memory.

Since `fork()` has been used, a process ID needs to be created. And the whole code is just going back and forth between the child and parent process.

## Running the code

Open the terminal and just run this code normally.

```bash
gcc -o shared_mem shared_mem.c
./shared_mem
# input your message
# to end the chat, press CTRL + C
```

However, as you might notice, the first iteration or the first message sent is not properly executed. <br> *I do not understand why it was executing like this, I tried to arrange it many times without any success.*

```python
# What is executed
Parent wrote: Child wrote: hello
Parent read: hello

# What is expecting 
Child wrote: hello
Parent read: hello
```

Without taking into account this unexpectly first message, the chat application is working quite fine.
