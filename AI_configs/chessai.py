import numpy as np
import chess
from tensorflow.keras.models import load_model

# Load the trained model
model = load_model('chess_dual_output_model.h5')

# Function to convert FEN to array
def fen_to_array(fen):
    board = chess.Board(fen)
    board_state = np.zeros(64)  # 8x8 board flattened into 64 positions
    for i in range(64):
        square = chess.square(i % 8, 7 - (i // 8))
        piece = board.piece_at(square)
        if piece:
            board_state[i] = piece.piece_type * (1 if piece.color == chess.WHITE else -1)
    return board_state

# Function to predict move
def predict_move(fen):
    board_state = fen_to_array(fen).reshape(1, -1)
    predictions = model.predict(board_state)
    from_square_index = np.argmax(predictions[0])
    to_square_index = np.argmax(predictions[1])
    from_square = chess.square_name(from_square_index)
    to_square = chess.square_name(to_square_index)
    return f"{from_square}{to_square}"

# Read FEN from input file and predict move
with open("board_state.txt", "r") as file:
    fen = file.read().strip()

predicted_move = predict_move(fen)

# Write the predicted move back to the file
with open("ai_move.txt", "w") as file:
    file.write(predicted_move)
