import speech_recognition as sr
import pyttsx3
from groq import Groq
import serial
import serial.tools.list_ports
import time
import os

class GroqChat:
    def __init__(self):
        # Initialize Groq API client
        api_key = os.getenv("GROQ_API_KEY", "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")
        self._client = Groq(api_key=api_key)
        self._model = "llama-3.3-70b-versatile"

        # Initialize text-to-speech engine
        self.tts_engine = pyttsx3.init()

        # Initialize serial connection to Arduino Uno
        self.arduino = None
        self.baudrate = 9600  # Matches Arduino Uno default
        self.port = None  # Will auto-detect port
        self.connect_to_arduino()

        # Valid commands (same as your animatronic eye commands)
        self.valid_commands = [
            "blink", "winkleft", "winkright", "doubleblink", "slowblink",
            "lookleft", "lookright", "lookup", "lookdown", "lookaround",
            "center", "halfclose", "randomblink", "randommove",
            "sad", "happy", "angry", "surprised", "tired", "curious", "talk"
        ]

    def connect_to_arduino(self):
        """Auto-detect and connect to Arduino Uno."""
        if self.arduino and self.arduino.is_open:
            self.arduino.close()
            print("Closed existing Arduino connection")

        # Auto-detect Arduino port
        ports = list(serial.tools.list_ports.comports())
        arduino_port = None
        for port in ports:
            if "Arduino" in port.description or "USB-SERIAL" in port.description:
                arduino_port = port.device
                break

        if not arduino_port:
            print("No Arduino Uno detected. Please connect the device.")
            return

        self.port = arduino_port
        print(f"Attempting to connect to Arduino Uno on {self.port}...")
        try:
            self.arduino = serial.Serial(port=self.port, baudrate=self.baudrate, timeout=1)
            time.sleep(2)  # Wait for connection to stabilize
            print(f"Connected to Arduino Uno on {self.port} at {self.baudrate} baud")
            self.arduino.write(b"test\n")  # Test command
            response = self.arduino.readline().decode('utf-8').strip()
            if response:
                print(f"Arduino response: {response}")
            else:
                print("No response from Arduino; check firmware or connection.")
        except serial.SerialException as e:
            print(f"Failed to connect to {self.port}: {e}")
            if "PermissionError" in str(e):
                print("Permission denied. Run the script as administrator or close other programs using the port.")
            self.arduino = None

    def get_response(self, prompt):
        """Get response from Groq API."""
        try:
            system_prompt = (
                f"You control an animatronic eye with these commands: {', '.join(self.valid_commands)}. "
                "If the input is a command (e.g., 'blink'), respond with 'cmd:<command>'. "
                "Otherwise, give a short answer."
            )
            completion = self._client.chat.completions.create(
                model=self._model,
                messages=[
                    {"role": "system", "content": system_prompt},
                    {"role": "user", "content": prompt}
                ],
                temperature=0.8,
                max_tokens=50,
                top_p=1,
                stream=True,
            )
            result = ""
            for chunk in completion:
                result += chunk.choices[0].delta.content or ""
            return result.strip()
        except Exception as e:
            print(f"Groq API error: {e}")
            return "Sorry, I can't process that right now."

    def speak(self, text):
        """Convert text to speech."""
        try:
            self.tts_engine.say(text)
            self.tts_engine.runAndWait()
        except Exception as e:
            print(f"Text-to-speech error: {e}")

    def send_to_arduino(self, command):
        """Send command to Arduino Uno."""
        if self.arduino and self.arduino.is_open:
            try:
                self.arduino.write(f"{command}\n".encode('utf-8'))
                print(f"Sent to Arduino: {command}")
                time.sleep(0.1)
                response = self.arduino.readline().decode('utf-8').strip()
                if response:
                    print(f"Arduino response: {response}")
            except serial.SerialException as e:
                print(f"Error sending to Arduino: {e}")
                self.connect_to_arduino()
        else:
            print("Arduino not connected")
            self.connect_to_arduino()

def recognize_speech():
    """Capture and recognize speech."""
    recognizer = sr.Recognizer()
    with sr.Microphone() as source:
        print("Listening... (Say 'blink', 'sad', or ask a question)")
        recognizer.adjust_for_ambient_noise(source, duration=1)
        try:
            audio = recognizer.listen(source, timeout=5)
            text = recognizer.recognize_google(audio).lower()
            print(f"You said: {text}")
            return text
        except sr.UnknownValueError:
            print("Could not understand audio.")
            return None
        except sr.RequestError as e:
            print(f"Speech recognition error: {e}")
            return None
        except sr.WaitTimeoutError:
            print("Timed out waiting for speech.")
            return None

# Main execution
if __name__ == "__main__":
    # Initialize chatbot
    groq_chat = GroqChat()

    # Test Arduino connection first
    if not groq_chat.arduino:
        print("Cannot proceed without Arduino Uno. Exiting.")
        exit()

    # Main loop
    while True:
        prompt = recognize_speech()
        if prompt:
            if prompt == "exit":
                print("Shutting down...")
                if groq_chat.arduino and groq_chat.arduino.is_open:
                    groq_chat.arduino.close()
                break

            response = groq_chat.get_response(prompt)
            print(f"AI: {response}")

            if response.startswith("cmd:"):
                command = response.split("cmd:")[1]
                groq_chat.send_to_arduino(command)
                groq_chat.speak(f"Executing {command}")
            else:
                groq_chat.send_to_arduino("talk")
                groq_chat.speak(response)

        time.sleep(1)  # Prevent tight looping
