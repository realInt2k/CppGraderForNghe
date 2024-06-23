import os
import subprocess
from flask import Flask, request, jsonify, redirect, render_template_string
from werkzeug.utils import secure_filename
from pathlib import Path

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = ''
app.config['ALLOWED_EXTENSIONS'] = {'cpp'}


def htmlStyles():
    return '''
        <style>
            .button {
                display: inline-block;
                padding: 10px 20px;
                font-size: 16px;
                color: white;
                background-color: #007bff;
                text-decoration: none;
                border-radius: 5px;
                border: none;
                cursor: pointer;
                text-align: center;
                transition: background-color 0.3s;
            }
            .button:hover {
                background-color: #0056b3;
            }
            body {
                font-family: Arial, sans-serif;
                margin: 20px;
                background-color: #f4f4f9;
            }
            .container {
                max-width: 800px;
                margin: auto;
                background: white;
                padding: 20px;
                border-radius: 8px;
                box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            }
            .section {
                margin-bottom: 20px;
            }
            .section h2 {
                margin-bottom: 10px;
                color: #333;
            }
            .section pre {
                background: #f9f9f9;
                padding: 10px;
                border-radius: 5px;
                border: 1px solid #ddd;
                white-space: pre-wrap;
                word-wrap: break-word;
            }
            .back-button {
                display: inline-block;
                padding: 10px 20px;
                font-size: 16px;
                color: white;
                background-color: #007bff;
                text-decoration: none;
                border-radius: 5px;
                margin-top: 20px;
            }
            .back-button:hover {
                background-color: #0056b3;
            }
            .d-flex {
                display: flex;
            }
            .justify-content-center {
                justify-content: center;
            }
            .mr-1 {
                margin-right: 1em;
            }
            .align-items-center {
                align-items: center;
            }
            .vh-100 {
                height: 100vh;
            }
            .vh-90 {
                height: 90vh;
            }
            .flex-column {
                flex-direction: column;
            }
            
        </style>
    '''

def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in app.config['ALLOWED_EXTENSIONS']

@app.route('/')
def index():
    return '''
    <!doctype html> ''' + htmlStyles() + '''
    <title>Grading Portal</title>
    <div class="align-items-center vh-90 d-flex justify-content-center flex-column">
        <h1>Upload new File</h1>
        <form class="" method=post enctype=multipart/form-data action="/upload">
        <input class="button mr-1" type=file name=file>
        <input class="button" type=submit value=Upload>
        </form>
    </div>
    '''

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return redirect(request.url)
    file = request.files['file']
    if file.filename == '':
        return redirect(request.url)
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(filepath)
        
        filenameNoExtension = Path(filepath).stem
        # return jsonify({
        #     'filename' : filename,
        #     'filepath' : filepath,
        #     'filenameNoExtension' : filenameNoExtension
        # });
        result = subprocess.run(['grade.bat', filenameNoExtension], capture_output=True, text=True)
        result = {
            'stdout': result.stdout,
            'stderr': result.stderr
        }
    
    html_template = '''
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Output</title>
        ''' + htmlStyles() + '''
    </head>
    <body>
        <div class="container">
            <div class="section">
                <h2>Filename</h2>
                <pre>{{ filename }}</pre>
            </div>
            <div class="section">
                <h2>Output</h2>
                <pre>{{ result.stdout }}</pre>
            </div>
            <div class="section">
                <h2>Errors</h2>
                <pre>{{ result.stderr }}</pre>
            </div>
            <a href="/" class="back-button">Back to Home</a>
        </div>
    </body>
    </html>
    '''
    
    return render_template_string(html_template, filename=filename, result=result)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80)