import socket

def main():
    # Create a server socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('0.0.0.0', 12345))
    server_socket.listen(5)

    print("Server is listening on 0.0.0.0:12345...")

    while True:
        # Accept incoming connections
        client_socket, client_address = server_socket.accept()
        print("Accepted connection from", client_address)

        # Receive data from the client
        data = client_socket.recv(1024)
        if not data:
            break

        # Split the data into separate fields
        data_fields = data.decode().split(',')
        car_id = data_fields[0]
        gps_location = data_fields[1]
        speed = data_fields[2]

        # Store the data in a dictionary
        car_data = {
            'car_id': car_id,
            'gps_location': gps_location,
            'speed': speed
        }

        # Broadcast the data to all other connected cars
        for other_client_socket, other_client_address in connected_clients:
            if other_client_socket != client_socket:
                other_client_socket.send(car_data)

        # Add the client to the list of connected clients
        connected_clients.append((client_socket, client_address))

if __name__ == '__main__':
    main()
