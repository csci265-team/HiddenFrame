/* eslint-disable @typescript-eslint/no-explicit-any */
import type { MetaFunction } from "@remix-run/node";
import { PageHeader, Button, Input } from "../components";
// import { useLoaderData } from "@remix-run/react";

export const meta: MetaFunction = () => {
    return [
        { title: "HiddenFrame" },
        { name: "description", content: "Welcome to Remix!" },
    ];
};

export async function loader() {
    // const resp = await fetch("https://api.unsplash.com/photos?per_page=1000", {
    //     headers: { Authorization: `Client-ID ${process.env.UNSPLASH_ACCESS_KEY}` },
    // });

    // if (resp.ok) return { photos: await resp.json() };
    // else return { photos: [] };
    return null
}

export default function Login() {

    return (
        <div className="flex items-center justify-center h-full">
            <div className="flex flex-col items-center gap-8 h-full">
                <PageHeader />

                <h2 className="text-2xl font-black ">Login</h2>

                <div className="flex flex-col gap-4 p-4">
                    <form className="flex flex-col gap-4 p-4">
                        <Input type="text" id="inviteId" name="inviteId" placeholder="Invite ID" disabled={true} value={"xyzABCAIdio"} />
                        <Input type="text" id="username" name="username" placeholder="Username" />
                        <Input type="password" id="password" name="password" placeholder="Password" />
                        <Button type="submit">Login</Button>
                    </form>
                </div>
            </div>
        </div>
    );
}
