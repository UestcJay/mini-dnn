/*
 * CNN demo for MNIST dataset
 * Author: Kai Han (kaihana@163.com)
 * Details in https://github.com/iamhankai/mini-dnn-cpp
 * Copyright 2018 Kai Han
 */
#include <Eigen/Dense>
#include <algorithm>
#include <iostream>

#include "layer.h"
#include "conv.h"
#include "fully_connected.h"
#include "ave_pooling.h"
#include "max_pooling.h"
#include "relu.h"
#include "sigmoid.h"
#include "softmax.h"
#include "loss.h"
#include "mse_loss.h"
#include "cross_entropy_loss.h"
#include "mnist.h"
#include "network.h"
#include "optimizer.h"
#include "sgd.h"


int main() {
	// data
	//std::string datadir = " D://c++repo//mini-dnn-cpp//data//mnist// ";
	//MNIST dataset("..\data\mnist\ ");
	printf("hello");
	MNIST dataset("");
	dataset.read();
	int n_train = dataset.train_data.cols();
	int dim_in = dataset.train_data.rows();
	std::cout << "mnist train number: " << n_train << std::endl;
	std::cout << "mnist test number: " << dataset.test_labels.cols() << std::endl;
	// dnn
	Network dnn;
	Layer* conv1 = new Conv(1, 28, 28, 4, 5, 5, 2, 2, 2);
	Layer* pool1 = new MaxPooling(4, 14, 14, 2, 2, 2);
	Layer* conv2 = new Conv(4, 7, 7, 16, 5, 5, 1, 2, 2);
	Layer* pool2 = new MaxPooling(16, 7, 7, 2, 2, 2);
	Layer* fc3 = new FullyConnected(pool2->output_dim(), 32);
	Layer* fc4 = new FullyConnected(32, 10);
	Layer* relu1 = new ReLU;
	Layer* relu2 = new ReLU;
	Layer* relu3 = new ReLU;
	Layer* softmax = new Softmax;
	dnn.add_layer(conv1);
	dnn.add_layer(relu1);
	dnn.add_layer(pool1);
	dnn.add_layer(conv2);
	dnn.add_layer(relu2);
	dnn.add_layer(pool2);
	dnn.add_layer(fc3);
	dnn.add_layer(relu3);
	dnn.add_layer(fc4);
	dnn.add_layer(softmax);
	// loss
	Loss* loss = new CrossEntropy;
	dnn.add_loss(loss);
	// train & test
	SGD opt(0.001, 5e-4, 0.9, true);
	// SGD opt(0.001);
	const int n_epoch = 5;
	const int batch_size = 128;
	for (int epoch = 0; epoch < n_epoch; epoch++) {
		shuffle_data(dataset.train_data, dataset.train_labels);
		for (int start_idx = 0; start_idx < n_train; start_idx += batch_size) {
			int ith_batch = start_idx / batch_size;
			Matrix x_batch = dataset.train_data.block(0, start_idx, dim_in,
				std::min(batch_size, n_train - start_idx));
			Matrix label_batch = dataset.train_labels.block(0, start_idx, 1,
				std::min(batch_size, n_train - start_idx));
			Matrix target_batch = one_hot_encode(label_batch, 10);
			if (false && ith_batch % 10 == 1) {
				std::cout << ith_batch << "-th grad: " << std::endl;
				dnn.check_gradient(x_batch, target_batch, 10);
			}
			dnn.forward(x_batch);
			dnn.backward(x_batch, target_batch);
			// display
			if (ith_batch % 50 == 0) {
				std::cout << ith_batch << "-th batch, loss: " << dnn.get_loss()
					<< std::endl;
			}
			// optimize
			dnn.update(opt);
		}
		// test
		dnn.forward(dataset.test_data);
		float acc = compute_accuracy(dnn.output(), dataset.test_labels);
		std::cout << std::endl;
		std::cout << epoch + 1 << "-th epoch, test acc: " << acc << std::endl;
		std::cout << std::endl;
	}
	system("pause");
	return 0;
}

