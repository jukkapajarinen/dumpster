export const fetchHelper = (endpoint, token, method, body) => {
  let url = 'https://taskman-jukkapajarinen.herokuapp.com/' + endpoint;
  let request = {
    headers: { 'Content-Type': 'application/json' },
    method: method,
  };
  if (token !== undefined)
    request['headers']['Authorization'] = 'Bearer ' + token;
  if ((method === 'post' || method === 'put') && body !== undefined )
    request['body'] = JSON.stringify(body);
  return fetch(url, request).then(res => res.json());
};