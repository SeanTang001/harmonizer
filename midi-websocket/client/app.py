from flask import Flask

app = Flask(__name__, static_folder='./', static_url_path='')


@app.route('/index')
def index():
    return app.send_static_file('index.html')

@app.route('/keyboard')
def keyboard():
    return app.send_static_file('keyboard.html')


if __name__ == '__main__':
    app.run(threaded=True, port=5000)