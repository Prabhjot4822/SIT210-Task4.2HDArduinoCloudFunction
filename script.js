// Your Firebase configuration
const firebaseConfig = {
  apiKey: "AIzaSyAQ2pTeUnmkoC_YCH092p5SbxyrttL0J5I",
  authDomain: "traffic-619c9.firebaseapp.com",
  databaseURL: "https://traffic-619c9-default-rtdb.firebaseio.com",
  projectId: "traffic-619c9",
  storageBucket: "traffic-619c9.appspot.com",
  messagingSenderId: "736192601469",
  appId: "1:736192601469:web:e4525ee1eb83b41dc18014"
};

// Initialize Firebase
firebase.initializeApp(firebaseConfig);

// Reference to the Firebase Realtime Database
const database = firebase.database();

// Function to reset LED statuses in the database when the page is closed
function resetLedStatusOnUnload() {
  database.ref('LEDs/').set({
    redLedStatus: 'RED OFF',
    greenLedStatus: 'GREEN OFF',
    blueLedStatus: 'BLUE OFF',
  });
}

// Add an event listener for the "beforeunload" event
window.addEventListener("beforeunload", function () {
  resetLedStatusOnUnload();
});

// Function to initialize LED statuses when the page loads
function initializeLEDStatus() {
  database.ref('LEDs/').once('value').then((snapshot) => {
    const ledStatus = snapshot.val();
    if (ledStatus) {
      // If there are no LED statuses in the database (first-time load), set default values
      document.getElementById('redStatus').textContent = 'RED OFF';
      document.getElementById('greenStatus').textContent = 'GREEN OFF';
      document.getElementById('blueStatus').textContent = 'BLUE OFF';

      // Set these default values in the database
      setLedStatus();
    }
  });
}

// Function to set LED statuses in the database
function setLedStatus() {
  const ledR = document.getElementById('redStatus').textContent;
  const ledG = document.getElementById('greenStatus').textContent;
  const ledB = document.getElementById('blueStatus').textContent;

  database.ref('LEDs/').set({
    redLedStatus: ledR,
    greenLedStatus: ledG,
    blueLedStatus: ledB,
  });
}

// Function to toggle RED LED status
function toggLedRED() {
  const redStatusElement = document.getElementById('redStatus');
  if (redStatusElement.textContent === 'RED OFF') {
    redStatusElement.textContent = 'RED ON';
  } else {
    redStatusElement.textContent = 'RED OFF';
  }

  setLedStatus();
}

// Function to toggle GREEN LED status
function toggLedGREEN() {
  const greenStatusElement = document.getElementById('greenStatus');
  if (greenStatusElement.textContent === 'GREEN OFF') {
    greenStatusElement.textContent = 'GREEN ON';
  } else {
    greenStatusElement.textContent = 'GREEN OFF';
  }

  setLedStatus();
}

// Function to toggle BLUE LED status
function toggLedBLUE() {
  const blueStatusElement = document.getElementById('blueStatus');
  if (blueStatusElement.textContent === 'BLUE OFF') {
    blueStatusElement.textContent = 'BLUE ON';
  } else {
    blueStatusElement.textContent = 'BLUE OFF';
  }

  setLedStatus();
}

// Call the initialization function when the page loads
initializeLEDStatus();