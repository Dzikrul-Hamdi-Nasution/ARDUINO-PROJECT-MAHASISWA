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



$(document).ready(function() {
  
  arus();
  suhu();
  tegangan();
  daya();
  status_alat();
  tes();
});

var kendali,kendali_2;
function tes() {
  var messagesRef = firebase.database().ref("manual");
  messagesRef.on('value', (snapshot) => {
      const data = snapshot.val();
      if(data=="0"){
        document.getElementById("kontrol").innerHTML ="Otomatis";
        checkbox1.checked = 1;
        kendali=1;
        document.getElementById("relay_kontrol").style.display = "none";
        document.getElementById("ini_tombol").style.display = "none";
      }else{
        document.getElementById("kontrol").innerHTML ="Manual";
        checkbox1.checked = 0;
        kendali=0;
        document.getElementById("relay_kontrol").style.display = "block";
        document.getElementById("ini_tombol").style.display = "block";
      }   
  });
  var checkbox1 = document.getElementById("customSwitches")

  var messagesRef = firebase.database().ref("relay");
  messagesRef.on('value', (snapshot) => {
      const data = snapshot.val();
      if(data=="0"){
        document.getElementById("relay_kontrol").innerHTML ="Relay : Off";
        checkbox2.checked = 0;
        kendali_2=1;
      }else{
        document.getElementById("relay_kontrol").innerHTML ="Relay : On";
        checkbox2.checked = 1;
        kendali_2=0;
      }   
  });
  var checkbox2 = document.getElementById("relay_switch")
	
}

function tombol_kendali(){
  if(kendali == 0){
    firebase.database().ref().update({
      manual: "0",
    });
    document.getElementById("relay_kontrol").style.display = "none";
    document.getElementById("ini_tombol").style.display = "none";
  }else{
    firebase.database().ref().update({
      manual: "1",
    });
    document.getElementById("relay_kontrol").style.display = "block";
    document.getElementById("ini_tombol").style.display = "block";
  }
}

function tombol_kendali_relay(){
  if(kendali_2 == 0){
    firebase.database().ref().update({
      relay: "0",
    });
    alert("Relay Mati");
  }else{
    firebase.database().ref().update({
      relay: "1",
    });
    alert("Relay Hidup");
  }
}

function status_alat() {
  var messagesRef = firebase.database().ref("status_beban");
  messagesRef.on('value', (snapshot) => {
      const data = snapshot.val();
      document.getElementById("Beban").innerHTML ="Beban : "+data;
  });
  var messagesRef = firebase.database().ref("manual");
  messagesRef.on('value', (snapshot) => {
      const data = snapshot.val();
      if(data=="0"){
        document.getElementById("kontrol").innerHTML ="Otomatis";
      }else{
        document.getElementById("kontrol").innerHTML ="Manual";
      }
      
  });
  var messagesRef = firebase.database().ref("status_start");
  messagesRef.on('value', (snapshot) => {
      const data = snapshot.val();
      document.getElementById("Start").innerHTML ="Start : "+data+".00 WIB";
  });
  var messagesRef = firebase.database().ref("status_stop");
  messagesRef.on('value', (snapshot) => {
      const data = snapshot.val();
      document.getElementById("Stop").innerHTML ="Stop : "+data+".00 WIB";
  });

}



function arus() {
  var messagesRef = firebase.database().ref("arus");
  messagesRef.on('value', (snapshot) => {
      const data = snapshot.val();
      $("#arus").val(data+ " mA");
  });
  var messagesRef = firebase.database().ref("set_arus");
  messagesRef.on('value', (snapshot) => {
      const data = snapshot.val();
      document.getElementById("parameter_arus").innerHTML ="Max Arus " +data +" mA";
  });
  
}

function suhu() {
  var messagesRef = firebase.database().ref("suhu");
  messagesRef.on('value', (snapshot) => {
      const data = snapshot.val();
      $("#suhu").val(data+ " Celcius");
  });
  var messagesRef = firebase.database().ref("set_suhu");
  messagesRef.on('value', (snapshot) => {
      const data = snapshot.val();
      document.getElementById("parameter_suhu").innerHTML ="Max Suhu " +data +" Celcius";
  });
}



function tegangan() {
  var max_tegangan,min_tegangan ;
  var messagesRef = firebase.database().ref("tegangan");
  messagesRef.on('value', (snapshot) => {
      const data = snapshot.val();
      $("#tegangan").val(data+ " Volt");
  });
  var messagesRef = firebase.database().ref("set_tegangan_max");
  messagesRef.on('value', (snapshot) => {
      const data = snapshot.val();
      max_tegangan=data;
  });
  var messagesRef = firebase.database().ref("set_tegangan_min");
  messagesRef.on('value', (snapshot) => {
      const data = snapshot.val();
      min_tegangan=data;
      document.getElementById("parameter_tegangan").innerHTML ="Offset " +min_tegangan +" - "+max_tegangan+" Volt";
  });
  
}

function daya() {
  var messagesRef = firebase.database().ref("kwh");
  messagesRef.on('value', (snapshot) => {
      const data = snapshot.val();
      $("#daya").val(data);
  });
  var messagesRef = firebase.database().ref("set_kwh");
  messagesRef.on('value', (snapshot) => {
      const data = snapshot.val();
      document.getElementById("parameter_kwh").innerHTML ="Max Kwh " +data;
  });
}

function oke() {
  firebase.auth().signOut();
  }

  
  function update_arus() {
      arus_baru = document.getElementById("set_arus").value;
      firebase.database().ref().update({
          set_arus: arus_baru,
        });
        alert("Arus Max telah di update");
  
   }

   function update_suhu() {
    suhu_baru = document.getElementById("set_suhu").value;
    firebase.database().ref().update({
      set_suhu: suhu_baru,
      });
      alert("Suhu Max telah di update");

 }


 function update_tegangan() {
  tegangan_baru_max = document.getElementById("set_tegangan_max").value;
  firebase.database().ref().update({
    set_tegangan_max: tegangan_baru_max,
    });

    tegangan_baru_min = document.getElementById("set_tegangan_min").value;
  firebase.database().ref().update({
    set_tegangan_min: tegangan_baru_min,
    });
    alert("Tegangan offset telah di update");

}

 function update_Kwh() {
  kwh_baru = document.getElementById("set_kwh").value;
  firebase.database().ref().update({
    set_kwh: kwh_baru,
    });
    alert("Kwh Max telah di update");

}

function non_Kwh() {
  kwh_baru = document.getElementById("set_kwh").value;
  firebase.database().ref().update({
    set_kwh: "0",
    });
    alert("Kwh Max di non-aktifkan");

}

  firebase.auth().onAuthStateChanged(function(user) {
      if (user) {
          // User is signed in.
         
         ///alert("Database telah di Sinkronkan");
      } else {
          // No user is signed in.
         // alert("Silahkan Login Kembali");
          //window.location.replace("index.html")
      }
    });


  










