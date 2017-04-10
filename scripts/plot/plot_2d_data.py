#!/usr/bin/env python2
import csv
import matplotlib.pylab as plt

TEST_DATA = "/tmp/dataset_test.csv"


def load_2d_data(fp, skip_header=True):
    csv_file = open(fp, 'r')
    csv_reader = csv.reader(csv_file)
    if skip_header:
        next(csv_reader, None)

    data = {
        "x": [], "y": [],
    }
    for line in csv_reader:
        data["x"].append(float(line[0]))
        data["y"].append(float(line[1]))

    return data


def plot(data):
    plt.figure()
    plt.plot(data["x"], data["y"])
    plt.show()


if __name__ == "__main__":
    data = load_2d_data(TEST_DATA)
    plot(data)
