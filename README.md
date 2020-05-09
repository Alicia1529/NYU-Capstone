# Setting
Modify the corresponding inputs either in `main/run.py` or under the `config` folder.

# Sequential version
In file `main/run.py`, set `parallel = False`
```
# locally
python3 main/run.py 

# cluster
srun -p parallel -N1 python3 main/run.py
```

# Distributed version
In file `main/run.py`, set `parallel = True`

Adjust the variable `worker_num` in file `deploy.sh` according to the `<num of nodes>` you run in the terminal
```
srun -p parallel --job-name=test --cpus-per-task=1 --nodes=<num of nodes> --tasks-per-node=1 --mem-per-cpu=1GB bash deploy.sh
```

