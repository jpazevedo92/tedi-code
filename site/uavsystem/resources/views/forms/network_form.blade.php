<form class="form-horizontal" action="{{isset($network) ? '/networks/'.$network->id : '/networks'}}" method="POST" enctype = "multipart/form-data">
    {{ isset($network) ? method_field('PATCH') : ''}}
    {{ csrf_field() }}
    <div class="form-group">
        <label class="control-label col-sm-3" for="if_name">Interface Name:</label>
        <div class="col-sm-3">
            <input type="text" class="form-control" id="if_name" placeholder="Enter interface name" name="if_name" value="{{ isset($network) ?  $network->if_name : null }}">
        </div>
        <label class="control-label col-sm-3" for="tunnel_ip_in">Tunnel IP in:</label>
        <div class="col-sm-3">
            <input type="text" class="form-control" id="tunnel_ip_in" placeholder="Enter Tunnel in IP" name="tunnel_ip_in" value="{{ isset($network) ?  $network->tunnel_ip_in : null }}">
        </div>
    </div>
    <div class="form-group">
        <label class="control-label col-sm-3" for="tunnel_ip_out">Tunnel IP out:</label>
        <div class="col-sm-3">
            <input type="text" class="form-control" id="tunnel_ip_out" placeholder="Enter Tunnel out IP" name="tunnel_ip_out" value="{{ isset($network) ?  $network->tunnel_ip_out : null }}">
        </div>
        <label class="control-label col-sm-3" for="network">Network Address:</label>
        <div class="col-sm-3">
            <input type="text" class="form-control" id="network_address" placeholder="Enter network adress" name="network_address" value="{{ isset($network) ?  $network->network_address : null }}">
        </div>
    </div>
    <div class="form-group">
        <label class="control-label col-sm-3" for="ip">Network Mask:</label>
        <div class="col-sm-3">
            <input type="text" class="form-control" id="mask" placeholder="Enter network mask" name="mask" value="{{ isset($network) ?  $network->mask : null }}">
        </div>
    </div>
    <div class="form-group">
        <div class="col-sm-offset-2 col-sm-10">
            <button type="submit" class="btn btn-default">{{ isset($network) ?  'Update' : 'Submit' }}</button>
        </div>
    </div> 
</form>