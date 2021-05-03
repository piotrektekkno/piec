const express = require("express");
const path = require("path");
const app = express();

let tempArray = new Array();


app.set("view engine", "ejs");
app.use(express.static(path.join(__dirname, "public")));

app.get("/", (req, res) => {
    res.render("index"); // index refers to index.ejs
});


app.post("/postTemp", (req, res) => {
  console.log('TEMP POST' + req.body.dtm);
  res.send('200:OK');
});

app.listen(process.env.PORT || 3000, () => {
  console.log("server started on port " +  3000 || process.env.PORT );
});