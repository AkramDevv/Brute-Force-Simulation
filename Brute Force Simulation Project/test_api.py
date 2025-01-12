from flask import Flask, request, jsonify

app = Flask(__name__)

users = {
    "test_user": "1234"
}


@app.route('/login', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')

    if username in users and users[username] == password:
        return jsonify({"status": "success", "message": "Login successfully!"})
    else:
        return jsonify({"status": "fail", "message": "Invalid credentials."})


if __name__ == '__main__':
    app.run(debug=True)
