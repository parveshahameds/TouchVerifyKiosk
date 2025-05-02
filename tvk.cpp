#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  // (RS, E, D4, D5, D6, D7)

// Navigation buttons
#define BTN_UP 8
#define BTN_SELECT 9
#define BTN_DOWN 10

// Additional buttons
#define BTN_SHOW_RESULT 11
#define BTN_RESET_VOTES 12
#define BUZZER_PIN 13

const int candidateCount = 5;  // Change this as needed (max 10)
int votes[10] = {0};  // Make sure this can handle your max number of candidates
int currentSelection = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_SELECT, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_SHOW_RESULT, INPUT_PULLUP);
  pinMode(BTN_RESET_VOTES, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  resetDisplay();
}

void loop() {
  if (Serial.available() > 0) {
    String receivedData = Serial.readStringUntil('\n');
    receivedData.trim();

    if (receivedData == "ALREADY_VOTED") {
      lcd.clear();
      lcd.print("Already Voted!");
      delay(3000);
      resetDisplay();
      Serial.println("VOTE_COMPLETED");
    } else {
      showCandidateSelection();
      processVote();
    }
  }

  if (digitalRead(BTN_SHOW_RESULT) == LOW) {
    delay(200);
    showResult();
  }

  if (digitalRead(BTN_RESET_VOTES) == LOW) {
    delay(200);
    resetVotes();
  }
}

void showCandidateSelection() {
  lcd.clear();
  lcd.print("Vote: Cand ");
  lcd.print(currentSelection + 1);
  lcd.setCursor(0, 1);
  lcd.print("UP SEL DOWN");
}

void processVote() {
  bool voteConfirmed = false;

  while (!voteConfirmed) {
    if (digitalRead(BTN_UP) == LOW) {
      currentSelection--;
      if (currentSelection < 0) currentSelection = candidateCount - 1;
      showCandidateSelection();
      delay(300);
    }

    if (digitalRead(BTN_DOWN) == LOW) {
      currentSelection++;
      if (currentSelection >= candidateCount) currentSelection = 0;
      showCandidateSelection();
      delay(300);
    }

    if (digitalRead(BTN_SELECT) == LOW) {
      voteConfirmed = true;
      delay(300);
    }
  }

  // Flashing confirmation
  for (int i = 0; i < 3; i++) {
    lcd.clear();
    delay(200);
    lcd.print("Processing...");
    delay(200);
  }

  votes[currentSelection]++;
  lcd.clear();
  lcd.print("Vote Accepted!");
  lcd.setCursor(0, 1);
  lcd.print("Cand ");
  lcd.print(currentSelection + 1);
  Serial.println("VOTE_COMPLETED");
  delay(3000);
  resetDisplay();
}

void showResult() {
  lcd.clear();

  bool noVotes = true;
  for (int i = 0; i < candidateCount; i++) {
    if (votes[i] > 0) {
      noVotes = false;
      break;
    }
  }

  if (noVotes) {
    lcd.print("No votes yet");
    delay(2000);
    resetDisplay();
    return;
  }

  // Display vote counts
  for (int i = 0; i < candidateCount; i++) {
    lcd.clear();
    lcd.print("Cand ");
    lcd.print(i + 1);
    lcd.print(": ");
    lcd.print(votes[i]);
    delay(1000);
  }

  int maxVotes = votes[0];
  for (int i = 1; i < candidateCount; i++) {
    if (votes[i] > maxVotes) {
      maxVotes = votes[i];
    }
  }

  lcd.clear();
  lcd.print("Winner(s):");
  lcd.setCursor(0, 1);
  String winners = "";

  for (int i = 0; i < candidateCount; i++) {
    if (votes[i] == maxVotes) {
      if (winners != "") winners += "&";
      winners += String(i + 1);
    }
  }

  lcd.print(winners);
  Serial.print(winners);

  // Buzzer
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }

  delay(4000);
  resetDisplay();
}

void resetVotes() {
  for (int i = 0; i < candidateCount; i++) {
    votes[i] = 0;
  }
  lcd.clear();
  lcd.print("Votes Cleared!");
  delay(3000);
  resetDisplay();
}

void resetDisplay() {
  lcd.clear();
  lcd.print("Place Finger...");
}
