import sys
import pandas as pd
import matplotlib.pyplot as plt

meta_parameter={0:"population size",1:"generations",2:"Mutation Distribution",3:"Mutation Probability",4:"Crossover Alpha",
                5:"Execution Time",6:"Problem",7:"seed"}

def get_sub_title(meta_data):
    meta_data_string=""
    for i in range(len(meta_data)):
        meta_data_string = meta_data_string + meta_parameter[i]+": " + meta_data[i]
        if(i<len(meta_data)-1):
            meta_data_string = meta_data_string + ", "
    return meta_data_string

def read_meta_data(index,directory):
    meta_data=[]
    with open(directory + "/meta_" + str(index + 1) + ".txt") as file:
        for line in file:
            meta_data.append(line.strip())
    return meta_data

compare_parameters={0:"pop: ",1:"gen: ",2:"mut dist: ",3:"mut prob: ",4:"alpha: "}

def get_diff_label(meta,compare):
    diff = []
    for comparison in compare_parameters.keys():
        if (compare[comparison] != meta[comparison]):
            diff.append(comparison)
            diff.append(meta[comparison])
    label = ""
    for i in range(0, len(diff), 2):
        label = label + compare_parameters[diff[i]] + diff[i+1]
        if(i<len(diff)-2):
            label = label + ", "
    return label


dir=sys.argv[3]+" "+sys.argv[4]
plt.style.use('seaborn-v0_8-paper')
if sys.argv[2]== "0":
    for i in range(int(sys.argv[1])):
        meta=read_meta_data(i,dir)
        df=pd.read_csv(dir+"/results_"+str(i+1)+".csv")
        fig1, ax1 = plt.subplots()
        plt.subplots_adjust(bottom=0.18)
        ax1.scatter(df["x1"],df["x2"])
        plt.xlabel('Objective 1')
        plt.ylabel('Objective 2')
        plt.figtext(0.5, 0.01, get_sub_title(meta), wrap=True, horizontalalignment='center', fontsize=10)
        plt.suptitle('Pareto Front '+str(i+1))
        plt.savefig(dir+"/Pareto_front_"+str(i+1)+".png", bbox_inches='tight')
        plt.close()

        df=pd.read_csv(dir+"/hypervolume_"+str(i+1)+".csv")
        fig2, ax2 = plt.subplots()
        plt.subplots_adjust(bottom=0.18)
        ax2.plot(df["hv"])
        plt.xlabel('generation')
        plt.ylabel('hypervolume')
        plt.figtext(0.5, 0.01, get_sub_title(meta), wrap=True, horizontalalignment='center', fontsize=10)
        plt.suptitle('Hypervolume '+str(i+1))
        plt.savefig(dir+"/Hypervolume_"+str(i+1)+".png", bbox_inches='tight')
        plt.close()


if sys.argv[2]== "1":
    fig, ax = plt.subplots()
    plt.subplots_adjust(bottom=0.18)
    compare=read_meta_data(0,dir)
    for i in range(int(sys.argv[1])):
        meta_data=read_meta_data(i,dir)
        if(i==0):
            label="baseline"
        else:
            label=get_diff_label(meta_data,compare)
        df=pd.read_csv(dir+"/hypervolume_"+str(i+1)+".csv")
        ax.plot(df["hv"],label=label)
    plt.xlabel('generation')
    plt.ylabel('hypervolume')
    plt.figtext(0.5, 0.01, get_sub_title(compare), wrap=True, horizontalalignment='center', fontsize=10)
    plt.suptitle('Hypervolume Comparison')
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    plt.savefig(dir+"/Hypervolume_comparison.png", bbox_inches='tight')

