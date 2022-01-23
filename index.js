const express = require("express");
const path = require("path");
const app = express();
const bodyParser = require('body-parser');
const { tmpdir } = require("os");

let tempArray = new Array();


app.use(express.json());       // to support JSON-encoded bodies
app.use(express.urlencoded()); // to support URL-encoded bodies


app.set("view engine", "ejs");
app.use(express.static(path.join(__dirname, "public")));

app.get("/", (req, res) => {
    res.render("index", {tArray: tempArray} ); // index refers to index.ejs
});


app.post("/postTemp", (req, res) => {
  let tm = new Date();
  tm = tm.toLocaleDateString('pl-PL') + ' ' + tm.toLocaleTimeString('pl-PL');
  
  req.body.dtm = tm;
  tempArray.push(req.body);
  if(tempArray.length > 19)
    tempArray.splice(0,19);
  console.log('TEMP POST' + req.body.dtm);
  console.log('TEMP POST' + req.body.sensor0);
  console.log('TEMP POST' + req.body.sensor1);
  res.send('200:OK');
});

app.listen(process.env.PORT || 3000, () => {
  console.log("server started on port " +  3000 || process.env.PORT );
});