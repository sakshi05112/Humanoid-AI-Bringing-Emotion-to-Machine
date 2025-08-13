#include <ESP32Servo.h>

// Global Servo declarations
Servo top_left_eyelid;
Servo bottom_left_eyelid;
Servo top_right_eyelid;
Servo bottom_right_eyelid;
Servo Yarm;
Servo Xarm;

String command = "";

// Function declarations
void moveServo(Servo &servo, int startAngle, int endAngle, int steps, int delayPerStep);
void quiverServo(Servo &servo, int baseAngle, int range, int cycles);
void random_movement();
void random_close();
void eye_ball_centert();
void close_eye();
void open_eye();
void synchronous_close();
void eye_ball_left();
void eye_ball_right();
void look_up();
void look_down();
void playSequence();
void talkAnimation();  // New function for natural eye movements

void setup() {
  top_left_eyelid.attach(5);
  bottom_left_eyelid.attach(12);
  top_right_eyelid.attach(33);
  bottom_right_eyelid.attach(4);
  Yarm.attach(18);
  Xarm.attach(19);
  
  Serial.begin(9600);
  delay(500);

  Serial.println("Initializing servos...");
  top_left_eyelid.write(90);
  bottom_left_eyelid.write(90);
  top_right_eyelid.write(90);
  bottom_right_eyelid.write(90);
  Yarm.write(90);
  Xarm.write(90);
  delay(1000);

  Serial.println("Opening eyes and centering...");
  open_eye();
  eye_ball_centert();
  delay(2000);

  Serial.println("Ready! Enter a command (e.g., 'blink', 'sad', 'talk'):");
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.readStringUntil('\n');
    command.trim();
    Serial.print("Received command: ");
    Serial.println(command);
    if (command == "test") {
      Serial.println("Arduino responding to test");
    } else {
      executeCommand(command);
      Serial.println("Done: " + command);
    }
  }
}

void executeCommand(String cmd) {
  if (cmd == "blink") {
    Serial.println("Executing: blink");
    for (int i = 0; i <= 10; i++) {
      top_left_eyelid.write(map(i, 0, 10, 2, 55));
      bottom_left_eyelid.write(map(i, 0, 10, 120, 36));
      top_right_eyelid.write(map(i, 0, 10, 46, 2));
      bottom_right_eyelid.write(map(i, 0, 10, 55, 160));
      delay(40);
    }
    delay(200);
    for (int i = 0; i <= 10; i++) {
      top_left_eyelid.write(map(i, 0, 10, 55, 2));
      bottom_left_eyelid.write(map(i, 0, 10, 36, 120));
      top_right_eyelid.write(map(i, 0, 10, 2, 46));
      bottom_right_eyelid.write(map(i, 0, 10, 160, 55));
      delay(40);
    }
  } else if (cmd == "winkleft") {
    Serial.println("Executing: winkleft");
    for (int i = 0; i <= 10; i++) {
      top_left_eyelid.write(map(i, 0, 10, 2, 55));
      bottom_left_eyelid.write(map(i, 0, 10, 120, 36));
      delay(40);
    }
    delay(420);
    for (int i = 0; i <= 10; i++) {
      top_left_eyelid.write(map(i, 0, 10, 55, 2));
      bottom_left_eyelid.write(map(i, 0, 10, 36, 120));
      delay(40);
    }
  } else if (cmd == "winkright") {
    Serial.println("Executing: winkright");
    for (int i = 0; i <= 10; i++) {
      top_right_eyelid.write(map(i, 0, 10, 46, 2));
      bottom_right_eyelid.write(map(i, 0, 10, 55, 160));
      delay(40);
    }
    delay(420);
    for (int i = 0; i <= 10; i++) {
      top_right_eyelid.write(map(i, 0, 10, 2, 46));
      bottom_right_eyelid.write(map(i, 0, 10, 160, 55));
      delay(40);
    }
  } else if (cmd == "doubleblink") {
    Serial.println("Executing: doubleblink");
    for (int i = 0; i <= 10; i++) {
      top_left_eyelid.write(map(i, 0, 10, 2, 55));
      bottom_left_eyelid.write(map(i, 0, 10, 120, 36));
      top_right_eyelid.write(map(i, 0, 10, 46, 2));
      bottom_right_eyelid.write(map(i, 0, 10, 55, 160));
      delay(40);
    }
    delay(200);
    for (int i = 0; i <= 10; i++) {
      top_left_eyelid.write(map(i, 0, 10, 55, 2));
      bottom_left_eyelid.write(map(i, 0, 10, 36, 120));
      top_right_eyelid.write(map(i, 0, 10, 2, 46));
      bottom_right_eyelid.write(map(i, 0, 10, 160, 55));
      delay(40);
    }
    delay(200);
    for (int i = 0; i <= 10; i++) {
      top_left_eyelid.write(map(i, 0, 10, 2, 55));
      bottom_left_eyelid.write(map(i, 0, 10, 120, 36));
      top_right_eyelid.write(map(i, 0, 10, 46, 2));
      bottom_right_eyelid.write(map(i, 0, 10, 55, 160));
      delay(40);
    }
    delay(200);
    for (int i = 0; i <= 10; i++) {
      top_left_eyelid.write(map(i, 0, 10, 55, 2));
      bottom_left_eyelid.write(map(i, 0, 10, 36, 120));
      top_right_eyelid.write(map(i, 0, 10, 2, 46));
      bottom_right_eyelid.write(map(i, 0, 10, 160, 55));
      delay(40);
    }
  } else if (cmd == "slowblink") {
    Serial.println("Executing: slowblink");
    for (int i = 0; i <= 20; i++) {
      top_left_eyelid.write(map(i, 0, 20, 2, 55));
      bottom_left_eyelid.write(map(i, 0, 20, 120, 36));
      top_right_eyelid.write(map(i, 0, 20, 46, 2));
      bottom_right_eyelid.write(map(i, 0, 20, 55, 160));
      delay(50);
    }
    delay(500);
    for (int i = 0; i <= 20; i++) {
      top_left_eyelid.write(map(i, 0, 20, 55, 2));
      bottom_left_eyelid.write(map(i, 0, 20, 36, 120));
      top_right_eyelid.write(map(i, 0, 20, 2, 46));
      bottom_right_eyelid.write(map(i, 0, 20, 160, 55));
      delay(50);
    }
  } else if (cmd == "lookleft") {
    Serial.println("Executing: lookleft");
    open_eye();
    moveServo(Xarm, 90, 40, 15, 40);
    delay(500);
    moveServo(Xarm, 40, 90, 15, 40);
  } else if (cmd == "lookright") {
    Serial.println("Executing: lookright");
    open_eye();
    moveServo(Xarm, 90, 140, 15, 40);
    delay(500);
    moveServo(Xarm, 140, 90, 15, 40);
  } else if (cmd == "lookup") {
    Serial.println("Executing: lookup");
    open_eye();
    moveServo(Yarm, 90, 132, 15, 40);
    delay(500);
    moveServo(Yarm, 132, 90, 15, 40);
  } else if (cmd == "lookdown") {
    Serial.println("Executing: lookdown");
    open_eye();
    moveServo(Yarm, 90, 45, 15, 40);
    delay(500);
    moveServo(Yarm, 45, 90, 15, 40);
  } else if (cmd == "lookaround") {
    Serial.println("Executing: lookaround");
    open_eye();
    moveServo(Xarm, 90, 50, 10, 50);
    delay(300);
    moveServo(Yarm, 90, 132, 10, 50);
    delay(300);
    moveServo(Xarm, 50, 130, 15, 50);
    delay(300);
    moveServo(Yarm, 132, 45, 15, 50);
    delay(300);
    eye_ball_centert();
  } else if (cmd == "center") {
    Serial.println("Executing: center");
    eye_ball_centert();
  } else if (cmd == "halfclose") {
    Serial.println("Executing: halfclose");
    moveServo(top_left_eyelid, 2, 30, 10, 50);
    moveServo(bottom_left_eyelid, 120, 80, 10, 50);
    moveServo(top_right_eyelid, 46, 25, 10, 50);
    moveServo(bottom_right_eyelid, 55, 100, 10, 50);
    delay(500);
  } else if (cmd == "randomblink") {
    Serial.println("Executing: randomblink");
    random_close();
  } else if (cmd == "randommove") {
    Serial.println("Executing: randommove");
    random_movement();
  } else if (cmd == "sad") {
    Serial.println("Executing: sad");
    for (int i = 0; i <= 20; i++) {
      top_left_eyelid.write(map(i, 0, 20, 2, 50));
      bottom_left_eyelid.write(map(i, 0, 20, 120, 70));
      top_right_eyelid.write(map(i, 0, 20, 46, 40));
      bottom_right_eyelid.write(map(i, 0, 20, 55, 90));
      Yarm.write(map(i, 0, 20, 90, 40));
      delay(60);
    }
    for (int j = 0; j < 3; j++) {
      synchronous_close();
      quiverServo(bottom_left_eyelid, 70, 3, 2);
      quiverServo(bottom_right_eyelid, 90, 3, 2);
      delay(300);
    }
    eye_ball_centert();
    open_eye();
  } else if (cmd == "happy") {
    Serial.println("Executing: happy");
    for (int i = 0; i <= 10; i++) {
      top_left_eyelid.write(map(i, 0, 10, 2, 0));
      bottom_left_eyelid.write(map(i, 0, 10, 120, 140));
      top_right_eyelid.write(map(i, 0, 10, 46, 55));
      bottom_right_eyelid.write(map(i, 0, 10, 55, 40));
      Yarm.write(map(i, 0, 10, 90, 130));
      delay(30);
    }
    moveServo(Xarm, 90, 70, 5, 40);
    delay(100);
    moveServo(Xarm, 70, 110, 10, 40);
    delay(100);
    moveServo(Xarm, 110, 90, 5, 40);
    open_eye();
  } else if (cmd == "angry") {
    Serial.println("Executing: angry");
    for (int i = 0; i <= 15; i++) {
      top_left_eyelid.write(map(i, 0, 15, 2, 40));
      bottom_left_eyelid.write(map(i, 0, 15, 120, 80));
      top_right_eyelid.write(map(i, 0, 15, 46, 20));
      bottom_right_eyelid.write(map(i, 0, 15, 55, 100));
      delay(40);
    }
    moveServo(Xarm, 90, 50, 10, 30);
    quiverServo(top_left_eyelid, 40, 3, 2);
    delay(300);
    moveServo(Xarm, 50, 130, 15, 30);
    delay(400);
    eye_ball_centert();
    open_eye();
  } else if (cmd == "surprised") {
    Serial.println("Executing: surprised");
    for (int i = 0; i <= 10; i++) {
      top_left_eyelid.write(map(i, 0, 10, 2, 0));
      bottom_left_eyelid.write(map(i, 0, 10, 120, 160));
      top_right_eyelid.write(map(i, 0, 10, 46, 55));
      bottom_right_eyelid.write(map(i, 0, 10, 55, 40));
      Yarm.write(map(i, 0, 10, 90, 140));
      delay(25);
    }
    delay(1500);
    open_eye();
  } else if (cmd == "tired") {
    Serial.println("Executing: tired");
    for (int i = 0; i <= 20; i++) {
      top_left_eyelid.write(map(i, 0, 20, 2, 50));
      bottom_left_eyelid.write(map(i, 0, 20, 120, 70));
      top_right_eyelid.write(map(i, 0, 20, 46, 40));
      bottom_right_eyelid.write(map(i, 0, 20, 55, 90));
      Yarm.write(map(i, 0, 20, 90, 60));
      delay(80);
    }
    delay(1500);
    eye_ball_centert();
    open_eye();
  } else if (cmd == "curious") {
    Serial.println("Executing: curious");
    for (int i = 0; i <= 10; i++) {
      top_left_eyelid.write(map(i, 0, 10, 2, 15));
      bottom_left_eyelid.write(map(i, 0, 10, 120, 110));
      top_right_eyelid.write(map(i, 0, 10, 46, 35));
      bottom_right_eyelid.write(map(i, 0, 10, 55, 70));
      delay(40);
    }
    moveServo(Xarm, 90, 60, 8, 30);
    delay(200);
    moveServo(Xarm, 60, 120, 12, 30);
    delay(200);
    moveServo(Yarm, 90, 120, 8, 30);
    delay(1000);
    eye_ball_centert();
    open_eye();
  } else if (cmd == "talk") {
    Serial.println("Executing: talk");
    talkAnimation();
  } else {
    Serial.println("Unknown command received.");
  }
}

// Helper function definitions
void moveServo(Servo &servo, int startAngle, int endAngle, int steps, int delayPerStep) {
  float stepSize = (float)(endAngle - startAngle) / steps;
  for (int i = 0; i <= steps; i++) {
    servo.write(startAngle + (int)(stepSize * i));
    delay(delayPerStep);
  }
}

void quiverServo(Servo &servo, int baseAngle, int range, int cycles) {
  for (int i = 0; i < cycles; i++) {
    servo.write(baseAngle + random(-range, range));
    delay(random(50, 100));
  }
}

void random_movement() {
  Xarm.write(60);
  delay(random(250, 340));
  Yarm.write(80);
  delay(random(250, 340));
  Xarm.write(120);
  delay(random(250, 340));
  Yarm.write(140);
  delay(random(250, 340));
  eye_ball_centert();
  delay(300);
  synchronous_close();
}

void random_close() {
  close_eye();
  delay(random(220, 880));
  open_eye();
  delay(random(220, 880));
}

void eye_ball_centert() {
  moveServo(Xarm, Xarm.read(), 90, 10, 50);
  moveServo(Yarm, Yarm.read(), 90, 10, 50);
}

void close_eye() {
  top_left_eyelid.write(55);
  bottom_left_eyelid.write(36);
  top_right_eyelid.write(2);
  bottom_right_eyelid.write(160);
  delay(40);
}

void open_eye() {
  top_left_eyelid.write(2);
  bottom_left_eyelid.write(120);
  top_right_eyelid.write(46);
  bottom_right_eyelid.write(55);
  delay(40);
}

void synchronous_close() {
  close_eye();
  delay(420);
  open_eye();
  delay(222);
}

void eye_ball_left() {
  Xarm.write(50);
}

void eye_ball_right() {
  Xarm.write(130);
}

void look_up() {
  Yarm.write(132);
}

void look_down() {
  Yarm.write(45);
}

void talkAnimation() {
  // Simulate natural eye movements during speech
  open_eye();
  for (int i = 0; i < 3; i++) {
    // Subtle glance left
    moveServo(Xarm, 90, 80, 5, 50);
    delay(random(200, 400));
    // Subtle glance right
    moveServo(Xarm, 80, 100, 5, 50);
    delay(random(200, 400));
    // Occasional slow blink
    if (random(0, 2) == 0) {
      for (int j = 0; j <= 10; j++) {
        top_left_eyelid.write(map(j, 0, 10, 2, 55));
        bottom_left_eyelid.write(map(j, 0, 10, 120, 36));
        top_right_eyelid.write(map(j, 0, 10, 46, 2));
        bottom_right_eyelid.write(map(j, 0, 10, 55, 160));
        delay(50);
      }
      delay(200);
      open_eye();
    }
    // Slight upward glance
    moveServo(Yarm, 90, 110, 5, 50);
    delay(random(200, 400));
    eye_ball_centert();
    delay(random(300, 600));
  }
  eye_ball_centert();
}
