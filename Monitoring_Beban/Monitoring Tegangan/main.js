var config = {
  apiKey: "AIzaSyC8nGP6QqXON_3PH6AmF5Ms6jBEfuGHnCY",
  authDomain: "monitoring-tegangan.firebaseapp.com",
  databaseURL: "https://monitoring-tegangan-default-rtdb.firebaseio.com",
  projectId: "monitoring-tegangan",
  storageBucket: "monitoring-tegangan.appspot.com",
  messagingSenderId: "252657501369",
  appId: "1:252657501369:web:a7e077dd5d2ef193570768",
  measurementId: "${config.measurementId}"
};
firebase.initializeApp(config);

var dbRef = firebase.database();
// Minggu pertama di hari senin

firebase.auth().onAuthStateChanged(function(user) {
  if (user) {
      // User is signed in.
      //window.location.replace("login/index.html")
     
  } else {
      // No user is signed in.
      
  }
});

function keluar() {
  firebase.auth().signOut();
}


var ulasan_tabel = dbRef.ref("log_data");
var table = document.getElementById("rekapitulasi").getElementsByTagName('tbody')[0];;

 //Memuat Data
 ulasan_tabel.on("child_added", function(data, prevChildKey) {
  var ulasan_data = data.val();

  var row = table.insertRow(table.rows.length);

  var u1 = row.insertCell(0);
  var u2 = row.insertCell(1);
  var u3 = row.insertCell(2);
  var u4 = row.insertCell(3);
  var u5 = row.insertCell(4);

 

  u1.innerHTML = ulasan_data.jam;
  u2.innerHTML = ulasan_data.suhu;
  u3.innerHTML = ulasan_data.tegangan;
  u4.innerHTML = ulasan_data.arus;
  u5.innerHTML = ulasan_data.kwh;


});

////////////////////////////////////////////////////////
//.........................................////////////
////////////////////////////////////////

function tombol() {
window.print();

}