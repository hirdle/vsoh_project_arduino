import cv2 
import numpy as np 

# Setup camera 
cap = cv2.VideoCapture(0) 
  
# While loop 
while True: 
    
    # Capture frame-by-frame 
    ret, frame = cap.read() 
      
    # Show the captured image
    cv2.namedWindow("Камера", cv2.WINDOW_NORMAL)
    cv2.setWindowProperty("Камера", cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN) 
    cv2.imshow('Камера', frame) 
      
    # wait for the key and come out of the loop 
    if cv2.waitKey(1) == ord('q'): 
        break
  
# Discussed below 
cap.release() 
cv2.destroyAllWindows() 