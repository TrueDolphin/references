#pip install scikit-image[option] opencv-python pyautogui
from skimage.metrics import mean_squared_error
import cv2
import numpy as np
import pyautogui
import time

def capture_screenshot():
    screenshot = pyautogui.screenshot()
    return np.array(screenshot), screenshot

def compare_images(imageA, imageB):
    small_size = (100, 75)
    resized_A = cv2.resize(imageA, small_size)
    resized_B = cv2.resize(imageB, small_size)
    mse = mean_squared_error(resized_A, resized_B)
    normalization_factor = 1000.0
    normalized_mse = (mse / normalization_factor) * 100.0
    return normalized_mse

def highlight_differences(imageA, imageB, threshold=0.9):
    grayA = cv2.cvtColor(imageA, cv2.COLOR_BGR2GRAY)
    grayB = cv2.cvtColor(imageB, cv2.COLOR_BGR2GRAY)
    diff_image = cv2.absdiff(grayA, grayB)
    _, thresh = cv2.threshold(diff_image, 50, 255, cv2.THRESH_BINARY)
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    for c in contours:
        x, y, w, h = cv2.boundingRect(c)
        cv2.rectangle(imageA, (x, y), (x + w, y + h), (255, 0, 0), 1)
    return imageA

def main():
    while True:
        screenshot1, _ = capture_screenshot()
        time.sleep(0.5)
        screenshot2, _ = capture_screenshot()

        difference = compare_images(screenshot1, screenshot2)
        print(f"Difference: {difference}")

        if difference > 15:
            diff_image = highlight_differences(screenshot1, screenshot2)
            h, w, _ = diff_image.shape
            resized_diff_image = cv2.resize(diff_image, (w // 2, h // 2))
            cv2.imwrite("difference.png", cv2.cvtColor(diff_image, cv2.COLOR_RGB2BGR))
            cv2.imshow("Display", cv2.cvtColor(resized_diff_image, cv2.COLOR_RGB2BGR))
            cv2.waitKey(1)

if __name__ == "__main__":
    main()
