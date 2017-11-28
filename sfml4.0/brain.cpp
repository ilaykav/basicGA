#include <vector>
#include <random>
#include <iostream>

class neuron
{
private:
	std::vector<float> weights;

public:
	void set_weights(std::vector<float> v) { this->weights = v; }
	float update(std::vector<float> inputs, int t)
	{
		//std::cout << "inputs = ";
		float sum = 0;
		for (int i = 0; i < inputs.size(); i++)
		{
			//std::cout << inputs[i] << ", ";
			sum += inputs[i] * weights[i];
			//std::cout << "weight = " << weights[i] << ", input =  " << inputs[i] << "sum = " << sum << std::endl;
		}
		sum -= t;
		float div = 1.0;
		float ret = (1 / (1 + exp(-sum /div)));
		//std::cout << "sum = " << sum << ", ret = " << ret << std::endl;
		//std::cout << std::endl << "sum = " << sum << std::endl << "final return value =" << ret;
		return ret;
	}
	std::vector<float> get_weights() { return weights; }
	neuron(int num_inputs){
		for (int i = 0; i < num_inputs; i++)
		{
			weights.push_back((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)*2-1));
		}
	}

	~neuron()
	{/*
		if (!weights.empty())
		{
			std::vector<float> tmpweights;
			weights.clear();
			weights.swap(tmpweights);
		}
	*/}
};


class neuron_line
{
private:
	float t = 0.5;
	int num_n;
	std::vector<neuron> neurons;

public:
	void set_weights(std::vector<std::vector<float>> v)
	{
		int index = 0;
		for (neuron &n : neurons)
		{
			n.set_weights(v[index]);
			index++;
		}
	}

	std::vector<std::vector<float>> get_weights() {
		std::vector<std::vector<float>> ret;
		for (neuron &i : neurons)
		{
			ret.push_back(i.get_weights());
		}
		return ret;
	}
	neuron_line(int num_n, int num_inputs)
	{
		for (int i = 0; i < num_n; i++)
		{
			neuron n(num_inputs);
			neurons.push_back(n);
		}
	}
	std::vector<float> update(std::vector<float> values)
	{
		//std::cout << "new line, values: " << std::endl;
		//for (float i : values) { std::cout << i << std::endl; }
		std::vector <float> ret;
		for (neuron &n : neurons)
		{
			ret.push_back(n.update(values, this->t));
		}
		return ret;
	}
	~neuron_line()
	{
		/*	if (!neurons.empty())
			{
				std::vector<neuron> tmpweights;
				for (neuron &n : neurons) { delete &n; }
				neurons.clear();
				neurons.swap(tmpweights);
			}
	*/
	}
};


class neural_network
{
private:
	std::vector<neuron_line> lines;

public:

	void set_c(std::vector<std::vector<std::vector<float>>> v)
	{
		int index = 0;
		for (neuron_line &nl : lines)
		{
			nl.set_weights(v[index]);
			index++;
		}
	}

	std::vector<std::vector<std::vector<float>>> get_weights()
	{
		std::vector<std::vector<std::vector<float>>> ret;
		for (neuron_line &i : lines)
		{
			ret.push_back(i.get_weights());
		}
		return ret;
	}
	
	neural_network(int num_inputs, int num_neurons_in_middle_lines, int num_middle_lines, int num_outputs)
	{
		lines.push_back(neuron_line(num_neurons_in_middle_lines, num_inputs));
		for (int i = 0; i < num_middle_lines; i++) {
			lines.push_back(neuron_line(num_neurons_in_middle_lines, num_neurons_in_middle_lines));
		}
		lines.push_back(neuron_line(num_outputs, num_neurons_in_middle_lines));
	}

	
	neural_network() {};
	
	
	~neural_network() 
	{
/*		if (!lines.empty())
		{
			std::vector<neuron_line> tmpweights;
			for (neuron_line &n : lines) { delete &n; }
			lines.clear();
			lines.swap(tmpweights);
		}
	*/}


	std::vector<float> get_results(std::vector<float> inputs)
	{
		//std::cout << "inputs = " << std::endl;
		//for (float i : inputs) { std::cout << i << std::endl; }
		for (neuron_line &nl : lines)
		{
			std::vector<float> in = nl.update(inputs);
			inputs = in;
		}
		//std::cout << "total outputs = " << std::endl;
		//for (float i : inputs) { std::cout << i << std::endl ; }
		return inputs;
	}
};
