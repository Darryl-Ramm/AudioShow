# AudioShow: Show AudioObjectShow() does not work as expected

 AudioShow: A simple demo that shows CoreAudio AudioObjectShow()
 not working as expected.
 
 This question is asked about in this Apple Developer Forum thread:
 https://developer.apple.com/forums/thread/748444

 I reached for AudioObjectShow() to help debug stuff but it does not
 appear to work on audio devices or audio streams. It prints nothing for
 them. It does work on kAudioObjectSystemObject, I've not explored what
 else it does or does not work on.
 
 I'm on macOS 14.4 with Xcode 15.3 on an Intel based Mac.

 This is a simple demo of the problem. We use AudioObjectShow() to print
 out info for the system kAudioObjectSystemObject which works as expected
 but then we look though all the audio devices in the system printing out
 their name (to show things are somewhat working) and then invoke
 AudioObjectShow() on them, which on my system produces no output. 
 
