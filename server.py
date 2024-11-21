import numpy as np
import cv2
from socket import socket, AF_INET, SOCK_STREAM
from concurrent.futures import ThreadPoolExecutor
from PIL import Image

def HandleRequest(mClientSocket, mClientAddr):
    print(f'Conexão aceita de {mClientAddr}')
    raw_data = b""
    end_delimiter = b"END_OF_IMAGE"

    try:
        while True:
            packet = mClientSocket.recv(8192)
            if not packet:
                break

            raw_data += packet
            # Verifica se o delimitador foi recebido
            if end_delimiter in raw_data:
                raw_data = raw_data.replace(end_delimiter, b"")
                break

    except Exception as e:
        print(f"Erro ao receber dados: {e}")
    finally:
        mClientSocket.close()

    if raw_data:
        frame_array = np.frombuffer(raw_data, dtype=np.uint8)
        img = cv2.imdecode(frame_array, cv2.IMREAD_UNCHANGED)

        if img is not None:
            # Convertendo para PIL e redimensionando
            image = Image.fromarray(img)
            image_resized = cv2.resize(np.array(image), (640, 480))

            # Salva a imagem redimensionada, se necessário
            output_path = "imagem_recebida_redimensionada.png"
            cv2.imwrite(output_path, image_resized)
            print(f"Imagem redimensionada salva em {output_path}")
            
            # Aqui você pode passar a 'image_resized' para o modelo de detecção de emoção
            # Por exemplo:
            # result = emotion_detection_model.predict(image_resized)

            # Enviar resposta de confirmação ao cliente
            rep = 'Imagem recebida e processada com sucesso.'
            print("Enviando resposta")
            mClientSocket.send(rep.encode())
        else:
            print("Erro ao decodificar a imagem recebida.")
    else:
        print("Nenhum dado foi recebido.")

def start_server():
    mSocketServer = socket(AF_INET, SOCK_STREAM)
    print(f'Socket criado ...')

    mSocketServer.bind(('127.0.0.1', 9595))
    mSocketServer.listen(10)
    print("Servidor levantado e escutando por conexões...")

    with ThreadPoolExecutor(max_workers=10) as executor:
        while True:
            clientSocket, clientAddr = mSocketServer.accept()
            print(f"O servidor aceitou a conexão do Cliente: {clientAddr}")
            executor.submit(HandleRequest, clientSocket, clientAddr)

if __name__ == "__main__":
    start_server()
