<form class="form-horizontal" action="{{isset($network) ? '/networks/'.$network->id : '/networks'}}" method="POST" enctype = "multipart/form-data">
    {{ isset($network) ? method_field('PATCH') : ''}}
    {{ csrf_field() }}
    <div class="form-group">
    <label class="control-label col-sm-3" for="address">Network Address:</label>
        <div class="col-sm-3">
            <input type="text" class="form-control" id="address" placeholder="Enter network adress" name="address" value="{{ isset($network) ?  $network->address : null }}">
        </div>
        <label class="control-label col-sm-3" for="mask">Network Mask:</label>
        <div class="col-sm-3">
            <input type="text" class="form-control" id="mask" placeholder="Enter network mask" name="mask" value="{{ isset($network) ?  $network->mask : null }}">
        </div>
    </div>
    <div class="form-group">
        <label class="control-label col-sm-3" for="ip_in">Tunnel IP in:</label>
        <div class="col-sm-3">
            <input type="text" class="form-control" id="ip_in" placeholder="Enter an IP address" name="ip_in" value="{{ isset($network) ?  $network->ip_in : null }}">
        </div>
        <label class="control-label col-sm-3" for="ip_out">Tunnel IP out:</label>
        <div class="col-sm-3">
            <input type="text" class="form-control" id="ip_out" placeholder="Enter an IP address" name="ip_out" value="{{ isset($network) ?  $network->ip_out : null }}">
        </div>

    </div>
    <div class="form-group">
        <div class="col-sm-offset-2 col-sm-10">
            <button type="submit" class="btn btn-default">{{ isset($network) ?  'Update' : 'Submit' }}</button>
        </div>
    </div> 
</form>