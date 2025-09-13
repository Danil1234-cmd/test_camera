# Camera Test Application

**⚠️ This program is used for testing the camera in the project [barcode](https://github.com/Danil1234-cmd/barcode).**

---

This project is a **test application for working with cameras** using **C++ and Qt Multimedia**.  
It was created to test camera functionality (preview, photo capture, switching between devices) that will be used in the main project: [barcode](https://github.com/Danil1234-cmd/barcode).

A lot of work has been done to:
- properly handle device enumeration and filtering (ignoring phantom devices),
- safely switch between cameras,
- capture and save images,
- provide error handling and clear status messages.

At this stage, the application is **still in testing**, and new features may be added or existing logic improved.  
External USB cameras will also be tested later for hot-plug and multi-device scenarios.

### Requirements
- C++17 or newer  
- Qt 6.x (Qt Multimedia, Qt Widgets)  
- CMake build system  

### Build instructions
```bash
git clone https://github.com/Danil1234-cmd/test_camera
cd test_camera
mkdir build && cd build
cmake ..
make -j$(nproc)
./camera
```

#### (Thank you for using my software)
