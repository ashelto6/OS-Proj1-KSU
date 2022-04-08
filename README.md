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
![Capture](https://user-images.githubusercontent.com/60279886/162364284-01bee468-6f4d-448b-91b3-ea7d9482d1f2.PNG)


