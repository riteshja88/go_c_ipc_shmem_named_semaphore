// https://medium.com/@glitchfix/ipc-shared-memory-concepts-of-c-in-golang-f539001226dc
package main

import (
    "fmt"
    "os"
	"golang.org/x/sys/unix"
	"semaphore"
)

func main() {
    // Create a key to identify the shared memory segment
    key := 1234

    // Create the shared memory segment with a size of 4096 bytes
    shmid, err := unix.SysvShmGet(key, 4096, 0666|unix.IPC_CREAT)
    if err != nil {
        fmt.Println("Error creating shared memory segment:", err)
        os.Exit(1)
    }

    // Attach to the shared memory segment
    data, err := unix.SysvShmAttach(shmid, 0, 0)
    if err != nil {
        fmt.Println("Error attaching to shared memory segment:", err)
        os.Exit(1)
    }

    // Write a string to the shared memory segment
    message := "Hello, World! from Golang"
    copy(data, []byte(message))
	fmt.Println("wrote to shmem: " + message)

    // Detach from the shared memory segment
    err = unix.SysvShmDetach(data)
    if err != nil {
        fmt.Println("Error detaching from shared memory segment:", err)
        os.Exit(1)
    }

	var sem semaphore.Semaphore
	if err := sem.Open("/testsem", 0644, 0); err != nil {
		fmt.Println("Failed to open: %v", err)
	}

	if err := sem.Post(); err != nil {
		fmt.Println("Failed to post: %v", err)
	}
	fmt.Println("sem_posted");

	if err := sem.Close(); err != nil {
		fmt.Println("Failed to close: %v", err)
	}



/*
	if err := sem.Unlink(); err != nil {
		t.Fatalf("Failed to unlink: %v", err)
	}
*/

    // Display the message read from the shared memory segment
    //fmt.Println("Message read from shared memory segment:", string(data))
}
