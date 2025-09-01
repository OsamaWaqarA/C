# Multithreaded Image Generator (C + pthreads)

This project is a C-based multithreaded application that generates random images and saves them as PNG files.  

The original task was to create a download simulator with a fake loading bar to mimic multithread communication. Instead, I implemented a real, working progress bar powered by true multithreading, mutex synchronization, and live thread tracking.  

I built the entire project in under 3 hours, demonstrating both technical depth and rapid development ability.  

---

## Features
- Runs multiple image generations in parallel using pthreads  
- User chooses the number of images to create  
- Supports multiple resolutions:  
  - 1280 × 720 (HD)  
  - 1920 × 1080 (Full HD)  
  - 3840 × 2160 (4K)  
  - 7680 × 4320 (8K)  
- Each image is filled with randomized color patterns and rectangles  
- Real-time, thread-synchronized progress bar  
- Outputs .png files via stb_image_write.h  

---

## Technologies Used
- C (core implementation)  
- pthreads (true multithreading)  
- stb_image_write.h (image export)  
- POSIX functions (sleep, mutex locks, etc.)  

---

## How It Works
1. User specifies how many images to generate.  
2. Each image runs inside its own thread, which:  
   - Allocates memory for pixel buffers  
   - Fills the buffer with randomized data  
   - Optionally adds random rectangles for variation  
   - Saves the final result as outputN.png  
3. Mutex-protected counters ensure safe communication between threads.  
4. A live progress bar reflects actual thread completion — not a simulation.  

---

## Project Structure
- main.c → Main program (thread creation + progress tracking)  
- stb_image_write.h → External library for PNG export  

---

## Skills Demonstrated
- Multithreading with pthreads  
- Thread synchronization using mutexes  
- Low-level memory management in C  
- External library integration (stb_image_write)  
- Systems programming under time pressure  

---

## Why This Project Stands Out
- Requirement: Fake loading bar to simulate multithread communication  
- My Solution: A real, concurrent program with a live progress bar and high-resolution outputs  
- Time Taken: Less than 3 hours  

This project showcases my ability to:  
- Exceed expectations with practical implementations  
- Solve problems under strict deadlines  
- Apply advanced systems programming concepts in a real application  
