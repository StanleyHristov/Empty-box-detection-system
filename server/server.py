from flask import Flask, request, jsonify

app = Flask(__name__)

X = 0.5
Y = 1.5

@app.route('/update_weights', methods=['POST'])
def update_weights():
    data = request.get_json()
    weight = data['weight']
    if X <= weight <= Y:
        return jsonify({"status": "OK"})
    else:
        return jsonify({"status": "Weight out of range"})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80, debug=True)
