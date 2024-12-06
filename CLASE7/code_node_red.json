[
    {
        "id": "a2cdc050d9223e93",
        "type": "tab",
        "label": "Flujo 41",
        "disabled": false,
        "info": "",
        "env": []
    },
    {
        "id": "1f5f21e01d4edfe9",
        "type": "inject",
        "z": "a2cdc050d9223e93",
        "name": "",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "4",
        "payloadType": "num",
        "x": 290,
        "y": 160,
        "wires": [
            [
                "39dc6be98f3a46e0"
            ]
        ]
    },
    {
        "id": "bb1fcb554d1106e0",
        "type": "debug",
        "z": "a2cdc050d9223e93",
        "name": "debug 41",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "false",
        "statusVal": "",
        "statusType": "auto",
        "x": 660,
        "y": 180,
        "wires": []
    },
    {
        "id": "f7c15391a1561e34",
        "type": "inject",
        "z": "a2cdc050d9223e93",
        "name": "",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "10",
        "payloadType": "num",
        "x": 290,
        "y": 220,
        "wires": [
            [
                "39dc6be98f3a46e0"
            ]
        ]
    },
    {
        "id": "39dc6be98f3a46e0",
        "type": "function",
        "z": "a2cdc050d9223e93",
        "name": "function 29",
        "func": "if(msg.payload>5){\n    msg.payload = \"Valor mayor que 5\";\n    return msg;\n}\nelse{\n    msg.payload = \"Valor menor o igual que 5\";\n    return msg;\n}\n",
        "outputs": 1,
        "timeout": 0,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 470,
        "y": 180,
        "wires": [
            [
                "bb1fcb554d1106e0"
            ]
        ]
    },
    {
        "id": "83849dec56300d11",
        "type": "serial in",
        "z": "a2cdc050d9223e93",
        "name": "",
        "serial": "ad5ef836ce78dbda",
        "x": 230,
        "y": 320,
        "wires": [
            [
                "99bf07df4814778f",
                "b5c5ffc08a4bacda"
            ]
        ]
    },
    {
        "id": "0299082b056cf70a",
        "type": "debug",
        "z": "a2cdc050d9223e93",
        "name": "debug 42",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "payload",
        "targetType": "msg",
        "statusVal": "",
        "statusType": "auto",
        "x": 640,
        "y": 400,
        "wires": []
    },
    {
        "id": "b28cca1a6c44d3bc",
        "type": "ui_gauge",
        "z": "a2cdc050d9223e93",
        "name": "",
        "group": "8f84c3b044ec4f6c",
        "order": 0,
        "width": 0,
        "height": 0,
        "gtype": "gage",
        "title": "gauge",
        "label": "units",
        "format": "{{value}}",
        "min": 0,
        "max": "4095",
        "colors": [
            "#00b500",
            "#e6e600",
            "#ca3838"
        ],
        "seg1": "",
        "seg2": "",
        "diff": false,
        "className": "",
        "x": 630,
        "y": 360,
        "wires": []
    },
    {
        "id": "99bf07df4814778f",
        "type": "function",
        "z": "a2cdc050d9223e93",
        "name": "function 30",
        "func": "let msg1 = {};\nmsg1.payload = msg.payload.split(\",\")[0];\nmsg.payload = msg.payload.split(\",\")[1];\n\nreturn [msg,msg1];",
        "outputs": 2,
        "timeout": 0,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 450,
        "y": 320,
        "wires": [
            [
                "7ee906ddbcdbf6f7"
            ],
            [
                "b28cca1a6c44d3bc",
                "9ba98b27e5f396e0"
            ]
        ]
    },
    {
        "id": "7ee906ddbcdbf6f7",
        "type": "ui_gauge",
        "z": "a2cdc050d9223e93",
        "name": "",
        "group": "8f84c3b044ec4f6c",
        "order": 1,
        "width": 0,
        "height": 0,
        "gtype": "gage",
        "title": "gauge",
        "label": "units",
        "format": "{{value}}",
        "min": 0,
        "max": "4095",
        "colors": [
            "#00b500",
            "#e6e600",
            "#ca3838"
        ],
        "seg1": "",
        "seg2": "",
        "diff": false,
        "className": "",
        "x": 630,
        "y": 280,
        "wires": []
    },
    {
        "id": "9ba98b27e5f396e0",
        "type": "ui_chart",
        "z": "a2cdc050d9223e93",
        "name": "",
        "group": "8f84c3b044ec4f6c",
        "order": 2,
        "width": 0,
        "height": 0,
        "label": "chart",
        "chartType": "line",
        "legend": "false",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "",
        "dot": false,
        "ymin": "0",
        "ymax": "4095",
        "removeOlder": 1,
        "removeOlderPoints": "",
        "removeOlderUnit": "3600",
        "cutout": 0,
        "useOneColor": false,
        "useUTC": false,
        "colors": [
            "#1f77b4",
            "#aec7e8",
            "#ff7f0e",
            "#2ca02c",
            "#98df8a",
            "#d62728",
            "#ff9896",
            "#9467bd",
            "#c5b0d5"
        ],
        "outputs": 1,
        "useDifferentColor": false,
        "className": "",
        "x": 630,
        "y": 320,
        "wires": [
            []
        ]
    },
    {
        "id": "b5c5ffc08a4bacda",
        "type": "function",
        "z": "a2cdc050d9223e93",
        "name": "function 31",
        "func": "msg.payload = msg.payload.split(\",\");\nreturn msg;",
        "outputs": 1,
        "timeout": 0,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 470,
        "y": 400,
        "wires": [
            [
                "0299082b056cf70a"
            ]
        ]
    },
    {
        "id": "ad5ef836ce78dbda",
        "type": "serial-port",
        "name": "PRUEBA ESP IDF",
        "serialport": "COM15",
        "serialbaud": "9600",
        "databits": "8",
        "parity": "none",
        "stopbits": "1",
        "waitfor": "",
        "dtr": "none",
        "rts": "none",
        "cts": "none",
        "dsr": "none",
        "newline": "\\n",
        "bin": "false",
        "out": "char",
        "addchar": "",
        "responsetimeout": "10000"
    },
    {
        "id": "8f84c3b044ec4f6c",
        "type": "ui_group",
        "name": "sensores",
        "tab": "e60218a82f62629f",
        "order": 1,
        "disp": true,
        "width": "6",
        "collapse": false,
        "className": ""
    },
    {
        "id": "e60218a82f62629f",
        "type": "ui_tab",
        "name": "ESP IDF IOT",
        "icon": "dashboard",
        "disabled": false,
        "hidden": false
    }
]
