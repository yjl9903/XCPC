import requests

url = 'http://129.204.197.72:7000'

r = requests.get(url)

print(r.status_code)
print(r.response)