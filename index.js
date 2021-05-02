const express = require("express");
const path = require("path");
const app = express();


app.set("view engine", "ejs");
app.use(express.static(path.join(__dirname, "public")));

app.get("/", (req, res) => {
    res.render("index"); // index refers to index.ejs
});

app.listen(process.env.port || 3000, () => {
  console.log("server started on port " + process.env.port || 3000);
});