# Task
## IReadStream
Design an interface (abstract class) that allows to read data from the stream of any nature (file, network, audio etc.). Interface design should meet the following requirements:
* _Non-blocking_. If the data being requested is temporarily unavailable: the client of the class must not be blocked by the call.
* _Streaming_. The amount of data that the stream can provide is expected to be enormously large. Interface design must not induce neither the client nor its implementations to consume a lot of memory.
* Error handling must be _exception-based_.

## FileReadStream
Provide implementation for IReadStream that reads data from the file specified by path using your favorite OS API. Although the FileReadStream implements a non-blocking interface, the implementation itself doesn’t have to be non-blocking.
In unit tests OS API usage is allowed
