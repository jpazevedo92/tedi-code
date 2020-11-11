import subprocess
import pingparsing
import json
import HTML
from robot.libraries.BuiltIn import BuiltIn

def icmp_ping(ip_to_ping, count, id_try):
    ping_parser = pingparsing.PingParsing()
    transmitter = pingparsing.PingTransmitter()
    transmitter.destination = ip_to_ping
    transmitter.count = count
    result = transmitter.ping()
    stats = json.loads(json.dumps(ping_parser.parse(result).as_dict(), indent=4)) 
    return stats

def multiple_icmp_ping(ip_to_ping, count, repetitions):
    table_data = []
    header_row = ['ID', 'Max(ms)', 'Min(ms)', 'Avg(ms)', 'Mdev(ms)']
    for i in range(int(repetitions)):
        id_try = int(i)+1
        stats = icmp_ping(ip_to_ping, count, id_try)
        table_data.append(
            [
                id_try, 
                stats['rtt_max'], 
                stats['rtt_min'], 
                stats['rtt_avg'], 
                stats['rtt_mdev']
            ]
        )
    htmlcode = HTML.table(table_data, header_row=header_row)
    BuiltIn().set_test_message("*HTML*" + htmlcode , "yes")


