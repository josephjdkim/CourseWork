#!/usr/bin/env python3
# Code by Joseph Kim
# github.com/josephjdkim

import numpy as np
import cv2

class NeuralNetwork():
    def __init__(self, hidden_size, alpha):
        # initialize properties of neural network size
        self.INPUT_SIZE = 784
        self.HIDDEN_SIZE = hidden_size
        self.OUTPUT_SIZE = 5
        self.ALPHA = alpha

        # initialize weights of synapse layers 1 and 2 respectively
        self.weights1 = (np.random.randn(self.INPUT_SIZE, self.HIDDEN_SIZE) - 0.5) * 2
        self.weights2 = (np.random.randn(self.HIDDEN_SIZE, self.OUTPUT_SIZE) - 0.5) * 2

    # sigmoid function for handling vector of values
    def sigmoid(self, A):
        B = []
        for x in A:
            B.append(1 / (1 + np.exp(-x)))
        return np.array(B)

    # sigmoid function for single values
    def sigmoid_s(self, x):
        return 1 / (1 + np.exp(-x))

    # derivative of sigmoid for handling vector of values
    def sigmoid_prime(self, A):
        B = []
        for x in A:
            B.append(self.sigmoid_s(x) * (1 - self.sigmoid_s(x)))
        return np.array(B)

    def feed_forward(self, X):
        self.hidden_layer = self.sigmoid(np.dot(X, self.weights1)) # produce hidden layer values using sigmoid
        self.output = self.sigmoid(np.dot(self.hidden_layer, self.weights2)) # produce output layer values
        return self.output

    def back_propagate(self, X, Y):
        self.feed_forward(X) # feed forward first

        output_error = Y - self.output # uses simple error functionn to calculate error
        output_delta = np.multiply(output_error, self.sigmoid_prime(self.output)) # calculate delta for output-hidden
        l1_delta = np.multiply(self.sigmoid_prime(self.hidden_layer), \
                    (np.dot(self.weights2, output_delta.T)).T) # calculate delta for hidden-input

        self.weights2 += self.ALPHA * np.matmul(self.hidden_layer.T, output_delta) # update weights for output-hidden
        self.weights1 += self.ALPHA * np.matmul(X.T, l1_delta) # update weights for hidden=input

# train NeuralNetwork with given input and expected output for given number of epochs
def train(nn, inp, outp, epochs):
    for e in range(0, epochs):
        nn.back_propagate(inp, outp)

def correctness(E, T): # experimental, theoretical
    num_correct = 0
    confusion_matrix = [[0, 0, 0, 0, 0], \
                        [0, 0, 0, 0, 0], \
                        [0, 0, 0, 0, 0], \
                        [0, 0, 0, 0, 0], \
                        [0, 0, 0, 0, 0]]
    for i in range(T.shape[0]): # number of inputs
        t = np.nonzero(T[i])[0][0] # expected value
        if np.sum(E[i]) > 1: # choose largest if more than one
            e = round(max(np.nonzero(E[i])[0]))
        elif np.sum(E[i]) == 0: # if all zeroes
            e = 0
        else:
            e = round(np.nonzero(E[i])[0][0])
        if t == e:
            num_correct += 1
        confusion_matrix[t][e] += 1 # update value of confusion matrix
    return (num_correct / T.shape[0], confusion_matrix) # return % correct and confusion matrix

if __name__ == "__main__":

    print("Importing training images...")
    train_images = []
    for i in range(0, 28038):
        image_name = "train/train_img/train_image_" + str(i) + ".bmp"
        img = cv2.imread(image_name, 0)
        train_images.append([item for sublist in img for item in sublist])
    train_images = np.array(train_images)

    print("Importing training labels...")
    train_expected = open("train/train_labels.txt", "r").read()
    train_expected = train_expected.split("\n")
    for i in range(0, len(train_expected)):
        train_expected[i] = [int(j) for j in train_expected[i].split()]
    train_expected = np.array(train_expected)

    print("Importing testing images...")
    test_images = []
    for i in range(0, 2561):
        image_name = "test/test_img/test_image_" + str(i) + ".bmp"
        img = cv2.imread(image_name, 0)
        test_images.append([item for sublist in img for item in sublist])
    test_images = np.array(test_images)

    print("Importing testing labels...")
    test_expected = open("test/test_labels.txt", "r").read()
    test_expected = test_expected.split("\n")
    for i in range(0, len(test_expected)):
        test_expected[i] = [int(j) for j in test_expected[i].split()]
    test_expected = np.array(test_expected)

    print("Importing complete.")

    # VARYING TESTS AND ANALYSES
    # runs training & analytics on NNs w/ hidden layers of size 50, 100, and 300
    possible_sizes = [50, 100, 300]
    for s in possible_sizes:
        print("=========== HIDDEN LAYER SIZE: " + str(s) + " ===========")
        print("Now training and testing with varying alphas:")
        for a in range(1, 10):
            alpha = a/10
            results, average_results = [], 0
            for i in range(0, 4):
                nn = NeuralNetwork(s, alpha)
                train(nn, train_images, train_expected, 50) # train for 50 epochs
                nn.feed_forward(test_images)
                results.append(correctness(nn.output, test_expected)[0])
                average_results += results[-1]
            # correctness_percentage, confusion_matrix = correctness(nn.output, test_expected)
            average_results = average_results / 4
            print("alpha=" + str(alpha) + " -- " + str(average_results * 100) + "%")

    # # EXAMPLE
    # # runs training & analytics on a Neural Network configured with optimal known settings (hidden_size=300, alpha=0.8)
    # NN = NeuralNetwork(300, 0.8)
    # train(NN, train_images, train_expected, 50)
    # NN.feed_forward(test_images)
    # correctness_percentage, confusion_matrix = correctness(NN.output, test_expected)
    # print("alpha=0.8 -- " + str(correctness_percentage * 100) + "%")
    # for cf in confusion_matrix:
    #     print(cf)
