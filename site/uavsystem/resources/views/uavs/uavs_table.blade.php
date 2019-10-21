<table style="width:100%">
        <thead>
            <tr>
                <th>Name</th>
                <th>Local IP</th>
                <th>Operations</th>
            </tr>
        </thead>
        <tbody>
        @foreach($uavs as $uav)

            <tr>
                <td>{{$uav->name}}</a></td> 
                <td>{{$uav->local_ip}}</td>
                <td>
                    <div class="form-group">
                        <form action="{{'/uavs/'.$uav->id }}" method="post">
                            {{ csrf_field() }}
                            {{method_field('DELETE')}}
                            <a href="{{'/uavs/'.$uav->id.'/edit' }}" class="btn btn-warning"><i class="fa fa-edit"></i></a>
                            <button type="submit" class="btn btn-danger btn-xl">
                            <i class="fa fa-trash"></i>
                            </button>
                        </form>
                    </div>
            </td>
            </tr>
        @endforeach
        </tbody>
    </table>