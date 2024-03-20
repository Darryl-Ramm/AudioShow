/*
  main.c
 
 AudioShow: A simple demo that tests if CoreAudio AudioObjectShow()
 works as expected.
 
 Created by Darryl Ramm on 3/14/24.

 I reached for AudioObjectShow() to help debug stuff but it does not
 appear to work on audio devices or audio streams. It prints nothing for
 them. It does work on kAudioObjectSystemObject, I've not explored what
 else it does or does not work on.
 
 I'm on macOS 14.4 with Xcode 15.3 on an Intel based Mac.

 This is a simple demo of the problem. We use AudioObjectShow() to print
 out info for the System kAudioObjectSystemObject which works as expected
 but then we look though all the audio devices in the system printing out
 their name (to show things are somewhat working) and then invoke
 AudioObjectShow() on them, which on my system produces no output. 
 

 */

/*
 Copyright (c) 2024 Darryl Ramm

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 */

#include <CoreAudio/AudioHardware.h>

static const AudioObjectPropertyAddress devicesAddress = {
    kAudioHardwarePropertyDevices,
    kAudioObjectPropertyScopeGlobal,
    kAudioObjectPropertyElementMain
    };

static const AudioObjectPropertyAddress nameAddress = {
    kAudioObjectPropertyName,
    kAudioObjectPropertyScopeGlobal,
    kAudioObjectPropertyElementMain
};

int main(int argc, const char *argv[]) {

    AudioObjectID *audioDevices;
    CFStringRef cfString;
    UInt32 size = sizeof(CFStringRef);
    
    AudioObjectGetPropertyDataSize(kAudioObjectSystemObject, &devicesAddress, 0, NULL, &size);
    audioDevices = (AudioObjectID *) malloc(size);
    
    AudioObjectGetPropertyData(kAudioObjectSystemObject, &devicesAddress, 0, NULL, &size, audioDevices);
    UInt32 nDevices = size / sizeof(AudioObjectID);
    
    printf("--- AudioObjectShow(kAudioObjectSystemObject):\n");
    AudioObjectShow(kAudioObjectSystemObject);

    for (int i=0; i < nDevices; i++) {
        printf("-------------------------------------------------\n");
        printf("audioDevices[%d] = 0x%x\n", i, audioDevices[i]);

        AudioObjectGetPropertyData(audioDevices[i], &nameAddress, 0, NULL, &size, &cfString);
        CFShow(cfString);

        //AudioObjectShow() give us anything?
        printf("--- AudioObjectShow(audioDevices[%d]=0x%x):\n", i, audioDevices[i]);
        AudioObjectShow(audioDevices[i]);
        printf("---\n");
    }
}

