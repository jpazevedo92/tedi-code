<form class="form-horizontal" action="{{isset($device) ? '/devices/'.$device->id : '/devices'}}" method="POST" enctype = "multipart/form-data">
    {{ isset($device) ? method_field('PATCH') : ''}}
    {{ csrf_field() }}
    <div class="form-group">
        <label class="control-label col-sm-1" for="Tag">Name:</label>
        <div class="col-sm-5">
            <input type="text" class="form-control" id="tag" placeholder="Enter device" name="name" value="{{ isset($device) ?  $device->name : null }}">
        </div>
        <label class="control-label col-sm-1" for="Tag">Network:</label>
        <div class="col-sm-5">
            <select name="network_id" class="form-control sel-status">
                <option value="0">Select one option</option>
                @foreach(App\Network::all() as $network)
                    <option value="{{$network->id}}" @if(isset($device) && $device->network->id == $network->id) selected @endif>{{$network->address != "none" ? $network->address : $network->ip_out}}</option>
                @endforeach
            </select>
        </div>
    </div>
    <div class="form-group">
        <div class="col-sm-offset-2 col-sm-10">
            <button type="submit" class="btn btn-default">{{ isset($mpls_tag) ?  'Update' : 'Submit' }}</button>
        </div>
    </div> 
</form>