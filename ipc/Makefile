.PHONY: shared_memory
shared_memory: shared_memory.c
		gcc -Werror -Wall shared_memory.c -o shared_memory
		./shared_memory

.PHONY: pipes
pipes: pipes.c
		gcc -Werror -Wall pipes.c -o pipes
		./pipes

.PHONY: message_queues
message_queues: message_queues.c
		gcc -Werror -Wall message_queues.c -o message_queues
		./message_queues

.PHONY: clean
clean:
		rm -rf shared_memory message_queues pipes