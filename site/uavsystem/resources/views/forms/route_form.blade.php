<form class="form-horizontal" action="{{isset($route) ? '/routes/'.$route->id : '/routes'}}" method="POST" enctype = "multipart/form-data">
    {{ isset($route) ? method_field('PATCH') : ''}}
    {{ csrf_field() }}

    <table style="width:100%">
        <thead>
                <tr>
                    <th>UAV</th>
                    <th>IN Interface</th>
                    <th>IN Label</th>
                    <th>OUT Interface</th>
                    <th>OUT Label</th>
                </tr>
        </thead>
        <tbody>
            <tr>
                <th>                        
                    <select name="uav_id"class="form-control js-example-theme-multiple" multiple="multiple" style="width: 75%">
                        <option value="0">Select one option</option>
                        @foreach(App\Uav::all() as $uav)
                            <option value="{{$uav->id}}" @if(isset($route) && $route->uav_id == $uav->id) selected @endif> {{$uav->name}} </option>
                        @endforeach
                    </select>
                </th>
                <th>
                    <select name="in_if_id" class="form-control js-example-theme-multiple" multiple="multiple" style="width: 75%">
                        <option value="0">Select one option</option>
                        @foreach(App\Device::all() as $device)
                            <option value="{{$device->id}}" @if(isset($route) && $route->in_if_id == $device->id) selected @endif> {{isset($route) && $route->in_if_id == null ? x : $device->name}}</option>
                        @endforeach
                    </select>
                </th>
                <th>
                    <select name="in_tag_id" class="form-control js-example-theme-multiple" multiple="multiple" style="width: 75%">
                        <option value="0">Select one option</option>
                        @foreach(App\MplsTag::all() as $mpls_tag)
                            <option value="{{$mpls_tag->id}}" @if ( isset($route) && $route->in_tag_id == $mpls_tag->id ) selected @endif> {{isset($route) && $route->in_tag_id == null ? x: $mpls_tag->tag}}</option>
                        @endforeach
                    </select>
                </th>
                <th>
                    <select name="out_if_id" class="form-control js-example-theme-multiple" multiple="multiple" style="width: 75%">
                        <option value="0">Select one option</option>
                        @foreach(App\Device::all() as $device)
                            <option value="{{$device->id}}" @if(isset($route) && $route->out_if_id == $device->id) selected @endif> {{$device->name}}</option>
                        @endforeach
                    </select>
                </th>
                <th>
                <select name="out_tag_id" class="form-control js-example-theme-multiple" multiple="multiple" style="width: 75%">
                        <option value="0">Select one option</option>
                        @foreach(App\MplsTag::all() as $mpls_tag)
                            <option value="{{$mpls_tag->id}}"  @if ( isset($route) && $route->out_tag_id == $mpls_tag->id ) selected @endif>{{$mpls_tag->tag}}</option>
                        @endforeach
                </select>
                </th>
            <tr>
        </tbody>
    </table>
    <div class="form-group">
        <div class="col-sm-offset-2 col-sm-10">
            <button type="submit" class="btn btn-default">{{ isset($route) ?  'Update' : 'Submit' }}</button>
        </div>
    </div> 
</form>