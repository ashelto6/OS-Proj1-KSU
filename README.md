# OS-Proj1-KSU
This program uses semaphores to solve the producer-consumer problem in the C programming language.

# Implementation
* A 2-item buffer exists in shared.h.
* producer.c & consumer.c share access to this buffer.
* When the buffer is full, the producer will wait until a consumer consumes an item from the buffer.
* When the buffer is empty, the consumer will wait under the producer places items in the buffer.

# Commands for Execution
``` 
gcc consumer.c -pthread -lrt -o consumer
gcc producer.c -pthread -lrt -o producer
./producer & ./consumer
```

# Example Output of 10 Producers/Consumers
![Capture](https://user-images.githubusercontent.com/60279886/162361581-3cb98fd7-475f-4ea0-b546-c38cab7c1d0d.PNG)

