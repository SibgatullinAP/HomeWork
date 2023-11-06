import numpy as np


class MyGaussianNBClassifier():
    def __init__(self, priors=None):
        self.priors = priors
        self.class_labels = None
        self.class_means = None
        self.class_variances = None

    def fit(self, X, y):
        self.class_labels = np.unique(y)
        self.class_means = {}
        self.class_variances = {}
        
        for label in self.class_labels:
            X_label = X[y == label]
            self.class_means[label] = np.mean(X_label, axis=0)
            self.class_variances[label] = np.var(X_label, axis=0)

    def predict(self, X):
        predictions = []
        for x in X:
            class_probs = []
            for label in self.class_labels:
                prior = self.priors[label] if self.priors else 1
                class_prob = -0.5 * np.sum(np.log(2 * np.pi * self.class_variances[label])) \
                             - 0.5 * np.sum(((x - self.class_means[label]) ** 2) / (self.class_variances[label]))
                class_probs.append(class_prob + np.log(prior))
            predictions.append(self.class_labels[np.argmax(class_probs)])
        return predictions

    def predict_proba(self, X):
        probabilities = []
        for x in X:
            class_probs = []
            for label in self.class_labels:
                prior = self.priors[label] if self.priors else 1
                class_prob = -0.5 * np.sum(np.log(2 * np.pi * self.class_variances[label])) \
                             - 0.5 * np.sum(((x - self.class_means[label]) ** 2) / (self.class_variances[label]))
                class_probs.append(class_prob + np.log(prior))
            log_probabilities = class_probs - np.max(class_probs)
            probabilities.append(np.exp(log_probabilities) / np.sum(np.exp(log_probabilities)))
        return probabilities

    def score(self, X, y):
        predictions = self.predict(X)
        accuracy = np.mean(predictions == y)
        return accuracy