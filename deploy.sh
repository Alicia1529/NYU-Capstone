# srun -p parallel --job-name=test --cpus-per-task=1 --nodes=2 --tasks-per-node=1 --mem-per-cpu=1GB bash deploy.sh

worker_num=1 # Must be one less that the total number of nodes

# module load Langs/Python/3.6.4 # This will vary depending on your environment
# source venv/bin/activate

nodes=$(scontrol show hostnames $SLURM_JOB_NODELIST) # Getting the node names

echo  "nodes are" $nodes
nodes_array=( $nodes )

node1=${nodes_array[0]}

echo "node1 is " $node1

ip_prefix=$(srun --nodes=1 --ntasks=1 -w $node1 hostname --ip-address) # Making address
suffix=':6379'
ip_head=$ip_prefix$suffix
redis_password=$(uuidgen)

echo "the ip_head is " $ip_head
export ip_head # Exporting for latter access by trainer.py

srun --nodes=1 --ntasks=1 -w $node1 ray start --block --head --redis-port=6379 --redis-password=$redis_password & # Starting the head
sleep 5

for ((  i=1; i<=$worker_num; i++ ))
do
  node2=${nodes_array[$i]}
  srun --nodes=1 --ntasks=1 -w $node2 ray start --block --address=$ip_head --redis-password=$redis_password & # Starting the workers
  sleep 5
done

python3 -u main/run.py $redis_password $worker_num # Pass the total number of allocated CPUs