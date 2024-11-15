from time import sleep
from random import random
from threading import Thread
from queue import Queue

def producer(queue):
    print('Producer: Running')
    for i in range(10):
        value = random()
        sleep(value)
        item = (i, value)
        queue.put(item)
        print(f'>producer added {item}')
    queue.put(None)
    print('Producer: Done')

def consumer(queue):
    print('Consumer: Running')
    while True:
        item = queue.get()
        if item is None:
            break
        sleep(item[1])
        print(f'>consumer got {item}')
    print('Consumer: Done')

queue = Queue()
consumer_thread = Thread(target=consumer, args=(queue,))
consumer_thread.start()
producer_thread = Thread(target=producer, args=(queue,))
producer_thread.start()
producer_thread.join()
consumer_thread.join()
