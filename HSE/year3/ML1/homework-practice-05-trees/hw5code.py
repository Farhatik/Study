import numpy as np
from collections import Counter, OrderedDict


def find_best_split(feature_vector, target_vector):
    sorted_inds = np.argsort(feature_vector)
    thresholds = (feature_vector[sorted_inds][:-1] + feature_vector[sorted_inds][1:]) / 2

    size_R_l = np.arange(thresholds.shape[0]) + 1
    size_R_r = size_R_l[::-1]

    cumsum_l = np.cumsum(target_vector[sorted_inds])[:-1]

    Hs_l = 1 - np.square((cumsum_l / size_R_l)) - np.square((size_R_l - cumsum_l) / size_R_l)
    sum_t_v = np.sum(target_vector)
    cumsum_r = sum_t_v - cumsum_l
    Hs_r = 1 - np.square(cumsum_r / size_R_r) - np.square((size_R_r - cumsum_r) / size_R_r)

    R_m = feature_vector.shape[0]
    ginis = -size_R_l / R_m * Hs_l - size_R_r / R_m * Hs_r
    threshold_best = thresholds[np.argmax(ginis)]
    gini_best = np.max(ginis)
    return thresholds, ginis, threshold_best, gini_best


class DecisionTree:
    def __init__(self, feature_types, max_depth=None, min_samples_split=None, min_samples_leaf=None):
        if np.any(list(map(lambda x: x != "real" and x != "categorical", feature_types))):
            raise ValueError("There is unknown feature type")

        self._tree = {}
        self._feature_types = feature_types
        self._max_depth = max_depth
        self._min_samples_split = min_samples_split
        self._min_samples_leaf = min_samples_leaf

    def _fit_node(self, sub_X, sub_y, node):
        if (np.unique(sub_y).shape[0] == 1):
            node["type"] = "terminal"
            node["class"] = sub_y[0]
            return
        if (sub_y.shape[0] <= 3):
            node["type"] = "terminal"
            node["class"] = Counter(sub_y).most_common(1)
            return

        feature_best, threshold_best, gini_best, split = None, None, None, None
        for feature in range(sub_X.shape[1]):
            feature_type = self._feature_types[feature]
            cat_ratio = {}
            if feature_type == "real":
                feature_vector = sub_X[:, feature]
            elif feature_type == "categorical":
                counts = Counter(sub_X[:, feature])
                clicks = Counter(sub_X[sub_y == 1, feature])
                ratio = {}
                for key, current_count in counts.items():
                    if key in clicks:
                        current_click = clicks[key]
                    else:
                        current_click = 0
                    ratio[key] = current_click / current_count
                feature_vector = np.array(list(map(lambda x: ratio[x], sub_X[:, feature])))
                cat_ratio = [(y, x) for x, y in ratio.items()]
                cat_ratio = sorted(cat_ratio)
            else:
                raise ValueError

            if len(feature_vector) < 3:
                node["type"] = "terminal"
                node["class"] = Counter(sub_y).most_common(1)
                return
            _, _, threshold, gini = find_best_split(feature_vector, sub_y)

            if gini_best is None or gini > gini_best:
                feature_best = feature
                gini_best = gini
                split = feature_vector < threshold

                if feature_type == "real":
                    threshold_best = threshold
                elif feature_type == "Categorical":
                    threshold_best = set()
                    for key, value in cat_ratio:
                        if key < threshold:
                            threshold_best.add(value)
                        else:
                            break
        if (split.sum() == sub_y.shape[0]):
            node["type"] = "terminal"
            node["class"] = Counter(sub_y).most_common(1)
            return
        node["feature_split"] = feature_best
        node["threshold"] = threshold_best
        print(feature_best, threshold_best)
        node["left_child"], node["right_child"] = {}, {}
        self._fit_node(sub_X[split], sub_y[split], node["left_child"])
        self._fit_node(sub_X[np.logical_not(split)], sub_y[np.logical_not(split)], node["right_child"])

    def _predict_node(self, x, node):
        pass

    def fit(self, X, y):
        self._fit_node(X, y, self._tree)

    def predict(self, X):
        predicted = []
        for x in X:
            predicted.append(self._predict_node(x, self._tree))
        return np.array(predicted)
