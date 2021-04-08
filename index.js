const http = require('http');
const port = process.env.PORT || 8081

const requestListener = function (req, res) {
  let dt = new Date;
  res.writeHead(200);
  res.end('Hello, World! ' + process.env.PORT + ' ' + dt.getUTCDate() );

}

const server = http.createServer(requestListener);
server.listen(port);
